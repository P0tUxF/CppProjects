import java.io.FileInputStream;
import java.io.FileNotFoundException;
import javafx.application.Application;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.layout.FlowPane;
import javafx.scene.control.Button;
import javafx.scene.control.Slider;
import javafx.scene.image.ImageView;
import javafx.scene.image.WritableImage;
import javafx.scene.image.PixelWriter;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import java.io.*;

public class Example extends Application {

	short cthead[][][]; //store the 3D volume data set
	short min, max; //min/max value in the 3D volume data set
	int CT_x_axis = 256;
	int CT_y_axis = 256;
	int CT_z_axis = 113;

	int topSliderValue = 76;
	int frontSliderValue = 76;
	int sideSliderValue = 76;
	double skinOpacitySliderValue = 0.12;


	@Override
	public void start(Stage stage) throws FileNotFoundException, IOException {
		stage.setTitle("CThead Viewer");
		ReadData();
		//Good practice: Define your top view, front view and side view images (get the height and width correct)
		//Here's the top view - looking down on the top of the head (each slice we are looking at is CT_x_axis x CT_y_axis)
		int Top_width = CT_x_axis;
		int Top_height = CT_y_axis;

		//Here's the front view - looking at the front (nose) of the head (each slice we are looking at is CT_x_axis x CT_z_axis)
		int Front_width = CT_x_axis;
		int Front_height = CT_z_axis;

		//and you do the other (side view) - looking at the ear of the head
		int Side_width = CT_y_axis;
		int Side_height = CT_z_axis;

		//We need 3 things to see an image
		//1. We create an image we can write to
		WritableImage top_image = new WritableImage(Top_width, Top_height);
		WritableImage front_image = new WritableImage(Front_width, Front_height);
		WritableImage side_image = new WritableImage(Side_width, Side_height);

		//2. We create a view of that image
		ImageView TopView = new ImageView(top_image);
		ImageView FrontView = new ImageView(front_image);
		ImageView SideView = new ImageView(side_image);


		Button slice76_button = new Button("slice76"); //an example button to get the slice 76
		Button volrend_button = new Button("volrend");
		//sliders to step through the slices (top and front directions) (remember 113 slices in top direction 0-112)
		Slider Top_slider = new Slider(0, CT_z_axis - 1, 0);
		Slider Front_slider = new Slider(0, CT_y_axis - 1, 0);
		Slider Side_slider = new Slider(0, CT_x_axis - 1, 0);
		Slider Skin_Opacity_Slider = new Slider(0, 1, 0);


		slice76_button.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent event) {
				Top_slider.setValue(76);
				Front_slider.setValue(76);
				Side_slider.setValue(76);
				TopDownSlice76(top_image);
				FrontBack(front_image);
				SideSide(side_image);
			}
		});

		volrend_button.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent event) {
				Skin_Opacity_Slider.setValue(0.12);
				transferFuncTop(top_image);
				transferFuncFront(front_image);
				transferFuncSide(side_image);
			}
		});

		Top_slider.valueProperty().addListener(
				new ChangeListener<Number>() {
					public void changed(ObservableValue<? extends Number> observable, Number oldValue, Number newValue) {
						System.out.println(newValue.intValue());
						topSliderValue = newValue.intValue();
						TopDownSlice76(top_image);
					}
				});

		Front_slider.valueProperty().addListener(new ChangeListener<Number>() {
			public void changed(ObservableValue<? extends Number> observable, Number oldValue, Number newValue) {
				System.out.println(newValue.intValue());
				frontSliderValue = newValue.intValue();
				FrontBack(front_image);
			}
		});

		Side_slider.valueProperty().addListener(new ChangeListener<Number>() {
			public void changed(ObservableValue<? extends Number> observable, Number oldValue, Number newValue) {
				System.out.println(newValue.intValue());
				sideSliderValue = newValue.intValue();
				SideSide(side_image);
			}
		});

		Skin_Opacity_Slider.valueProperty().addListener(new ChangeListener<Number>() {
			@Override
			public void changed(ObservableValue<? extends Number> observable, Number oldValue, Number newValue) {
				System.out.println(newValue.doubleValue());

				skinOpacitySliderValue = newValue.doubleValue();
				transferFuncTop(top_image);
				transferFuncFront(front_image);
				transferFuncSide(side_image);

			}
		});

		FlowPane root = new FlowPane();
		root.setVgap(8);
		root.setHgap(3);

//https://examples.javacodegeeks.com/desktop-
// java/javafx/scene/image-scene/javafx-image-example/

		//3. (referring to the 3 things we need to display an image)
		//we need to add it to the flow pane
		root.getChildren().addAll(TopView, FrontView, SideView, slice76_button, volrend_button, Top_slider, Front_slider, Side_slider, Skin_Opacity_Slider);

		Scene scene = new Scene(root, 900, 480);
		stage.setScene(scene);
		stage.show();
	}

	//Function to read in the cthead data set
	public void ReadData() throws IOException {
		//File name is hardcoded here - much nicer to have a dialog to select it and capture the size from the user
		File file = new File("C:\\Users\\Ian Lavin Rady\\Downloads\\CThead");
		//Read the data quickly via a buffer (in C++ you can just do a single fread - I couldn't find if there is an equivalent in Java)
		DataInputStream in = new DataInputStream(new BufferedInputStream(new FileInputStream(file)));
		int i, j, k; //loop through the 3D data set
		min = Short.MAX_VALUE;
		max = Short.MIN_VALUE; //set to extreme values
		short read; //value read in
		int b1, b2; //data is wrong Endian (check wikipedia) for Java so we need to swap the bytes around
		cthead = new short[CT_z_axis][CT_y_axis][CT_x_axis]; //allocate the memory - note this is fixed for this data set
		//loop through the data reading it in
		for (k = 0; k < CT_z_axis; k++) {
			for (j = 0; j < CT_y_axis; j++) {
				for (i = 0; i < CT_x_axis; i++) {
					//because the Endianess is wrong, it needs to be read byte at a time and swapped
					b1 = ((int) in.readByte()) & 0xff; //the 0xff is because Java does not have unsigned types
					b2 = ((int) in.readByte()) & 0xff; //the 0xff is because Java does not have unsigned types
					read = (short) ((b2 << 8) | b1); //and swizzle the bytes around
					if (read < min) min = read; //update the minimum
					if (read > max) max = read; //update the maximum
					cthead[k][j][i] = read; //put the short into memory (in C++ you can replace all this code with one fread)
				}
			}
		}
		System.out.println(min + " " + max); //diagnostic - for CThead this should be -1117, 2248
		//(i.e. there are 3366 levels of grey (we are trying to display on 256 levels of grey)
		//therefore histogram equalization would be a good thing
		//maybe put your histogram equalization code here to set up the mapping array
	}

	/*
	   This function shows how to carry out an operation on an image.
	   It obtains the dimensions of the image, and then loops through
	   the image carrying out the copying of a slice of data into the
	   image.
   */
	public void TopDownSlice76(WritableImage image) {
		//Get image dimensions, and declare loop variables
		int w = (int) image.getWidth(), h = (int) image.getHeight();
		PixelWriter image_writer = image.getPixelWriter();
		double col;
		short datum;
		//Shows how to loop through each pixel and colour
		//Try to always use j for loops in y, and i for loops in x
		//as this makes the code more readable
		for (int j = 0; j < h; j++) {
			for (int i = 0; i < w; i++) {
				//at this point (i,j) is a single pixel in the image
				//here you would need to do something to (i,j) if the image size
				//does not match the slice size (e.g. during an image resizing operation
				//If you don't do this, your j,i could be outside the array bounds
				//In the framework, the image is 256x256 and the data set slices are 256x256
				//so I don't do anything - this also leaves you something to do for the assignment
				datum = cthead[topSliderValue][j][i]; //get values from slice 76 (change this in your assignment)
				//calculate the colour by performing a mapping from [min,max] -> 0 to 1 (float)
				//Java setColor uses float values from 0 to 1 rather than 0-255 bytes for colour
				col = (((float) datum - (float) min) / ((float) (max - min)));
				image_writer.setColor(i, j, Color.color(col, col, col, 1.0));
			} // column loop
		} // row loop
	}

	public void FrontBack(WritableImage image) {
		int w = (int) image.getWidth(), h = (int) image.getHeight();
		PixelWriter image_writer = image.getPixelWriter();
		double col;
		short datum;
		for (int j = 0; j < h; j++) {
			for (int i = 0; i < w; i++) {
				datum = cthead[j][frontSliderValue][i];
				col = (((float) datum - (float) min) / ((float) (max - min)));
				image_writer.setColor(i, j, Color.color(col, col, col, 1.0));
			}
		}
	}

	public void SideSide(WritableImage image) {
		int w = (int) image.getWidth(), h = (int) image.getHeight();
		PixelWriter image_writer = image.getPixelWriter();
		double col;
		short datum;
		for (int j = 0; j < h; j++) {
			for (int i = 0; i < w; i++) {
				datum = cthead[j][i][sideSliderValue];
				col = (((float) datum - (float) min) / ((float) (max - min)));
				image_writer.setColor(i, j, Color.color(col, col, col, 1.0));
			}
		}
	}

	public void transferFuncTop(WritableImage image) {
		int w = (int) image.getWidth(), h = (int) image.getHeight();
		PixelWriter image_writer = image.getPixelWriter();
		short datum;
		double red;
		double green;
		double blue;
		double transparency;
		double opacity;
		double lightComingIn;
		for (int j = 0; j < h; j++) {
			for (int i = 0; i < w; i++) {
				red = 0;
				blue = 0;
				green = 0;
				transparency = 1;
				lightComingIn = 1;
				for (int k = 0; k <= 112; k++) {
					datum = cthead[k][j][i];
					if (datum < -300) {
						opacity = 0;
						red += transparency * opacity * 1 * lightComingIn * 0;
						green += transparency * opacity * 1 * lightComingIn * 0;
						blue += transparency * opacity * 1 * lightComingIn * 0;
						transparency = transparency *  (1 - opacity);

					} else if (datum >= -300 && datum <= 49) {
						opacity = skinOpacitySliderValue;
						red += transparency * ((opacity) * 1 * lightComingIn * 1.0);
						green += transparency * ((opacity) * 1 * lightComingIn * 0.79);
						blue += transparency * ((opacity) * 1 * lightComingIn * 0.6);
						transparency = transparency *  (1 - opacity);


					} else if (datum >= 50 && datum <= 299) {
						opacity = 0;
						red += transparency * ((opacity) * 1 * lightComingIn * 0);
						green += transparency * ((opacity) * 1 * lightComingIn * 0);
						blue += transparency * ((opacity) * 1 * lightComingIn * 0);
						transparency = transparency *  (1 - opacity);

					} else if (datum >= 300 && datum <= 4096) {
						opacity = 0.8;
						red += transparency * ((opacity) * 1 * lightComingIn * 1);
						green += transparency * ((opacity) * 1 * lightComingIn * 1);
						blue += transparency * ((opacity) * 1 * lightComingIn * 1);
						transparency = transparency * (1 - opacity);
					}
					if (red > 1) {
						red = 1;
					}

					if (green > 1) {
						green = 1;
					}

					if (blue > 1) {
						blue = 1;
					}
				}

				image_writer.setColor(i, j, Color.color(red, green, blue, 1));
			}
		}
	}

	public void transferFuncFront(WritableImage image) {
		int w = (int) image.getWidth(), h = (int) image.getHeight();
		PixelWriter image_writer = image.getPixelWriter();
		short datum;
		double red;
		double green;
		double blue;
		double transparency;
		double opacity;
		double lightComingIn;
		for (int j = 0; j < h; j++) {
			for (int i = 0; i < w; i++) {
				red = 0;
				blue = 0;
				green = 0;
				transparency = 1;
				lightComingIn = 1;
				for (int k = 0; k <= 112; k++) {
					datum = cthead[j][k][i];
					if (datum < -300) {
						opacity = 0;
						red += transparency * opacity * 1 * lightComingIn * 0;
						green += transparency * opacity * 1 * lightComingIn * 0;
						blue += transparency * opacity * 1 * lightComingIn * 0;
						transparency = transparency *  (1 - opacity);

					} else if (datum >= -300 && datum <= 49) {
						opacity = skinOpacitySliderValue;
						red += transparency * ((opacity) * 1 * lightComingIn * 1.0);
						green += transparency * ((opacity) * 1 * lightComingIn * 0.79);
						blue += transparency * ((opacity) * 1 * lightComingIn * 0.6);
						transparency = transparency *  (1 - opacity);

					} else if (datum >= 50 && datum <= 299) {
						opacity = 0;
						red += transparency * ((opacity) * 1 * lightComingIn * 0);
						green += transparency * ((opacity) * 1 * lightComingIn * 0);
						blue += transparency * ((opacity) * 1 * lightComingIn * 0);
						transparency = transparency *  (1 - opacity);

					} else if (datum >= 300 && datum <= 4096) {
						opacity = 0.8;
						red += transparency * ((opacity) * 1 * lightComingIn * 1);
						green += transparency * ((opacity) * 1 * lightComingIn * 1);
						blue += transparency * ((opacity) * 1 * lightComingIn * 1);
						transparency = transparency *  (1 - opacity);
					}
					if (red > 1) {
						red = 1;
					}

					if (green > 1) {
						green = 1;
					}

					if (blue > 1) {
						blue = 1;
					}
				}
				image_writer.setColor(i, j, Color.color(red, green, blue, 1));
			}
		}
	}

	public void transferFuncSide(WritableImage image) {
		int w = (int) image.getWidth(), h = (int) image.getHeight();
		PixelWriter image_writer = image.getPixelWriter();
		short datum;
		double red;
		double green;
		double blue;
		double transparency;
		double opacity;
		double lightComingIn;

		for (int j = 0; j < h; j++) {
			for (int i = 0; i < w; i++) {
				red = 0;
				blue = 0;
				green = 0;
				transparency = 1;
				lightComingIn = 1;
				for (int k = 0; k <= 112; k++) {
					datum = cthead[j][i][k];
					if (datum < -300) {
						opacity = 0;
						red += transparency * opacity * 1 * lightComingIn * 0;
						green += transparency * opacity * 1 * lightComingIn * 0;
						blue += transparency * opacity * 1 * lightComingIn * 0;
						transparency = transparency *  (1 - opacity);

					} else if (datum >= -300 && datum <= 49) {
							opacity = skinOpacitySliderValue;
							red += transparency * ((opacity) * 1 * lightComingIn * 1.0);
							green += transparency * ((opacity) * 1 * lightComingIn * 0.79);
							blue += transparency * ((opacity) * 1 * lightComingIn * 0.6);
							transparency = transparency *  (1 - opacity);

					} else if (datum >= 50 && datum <= 299) {
							opacity = 0;
							red += transparency * ((opacity) * 1 * lightComingIn * 0);
							green += transparency * ((opacity) * 1 * lightComingIn * 0);
							blue += transparency * ((opacity) * 1 * lightComingIn * 0);
							transparency = transparency *  (1 - opacity);

					} else if (datum >= 300 && datum <= 4096) {
							opacity = 0.8;
							red += transparency * ((opacity) * 1 * lightComingIn * 1);
							green += transparency * ((opacity) * 1 * lightComingIn * 1);
							blue += transparency * ((opacity) * 1 * lightComingIn * 1);
							transparency = transparency *  (1 - opacity);
					}
					if (red > 1) {
						red = 1;
					}

					if (green > 1) {
						green = 1;
					}

					if (blue > 1) {
						blue = 1;
					}
				}
				image_writer.setColor(i, j, Color.color(red, green, blue, 1));


			}
		}
	}

	public static void main(String[] args) {
		launch();
	}
}

