<?php

namespace Database\Factories;

use Illuminate\Database\Eloquent\Factories\Factory;
use App\Models\User;
class PostFactory extends Factory
{
      /** The name of the facory's corresponding model.
        @var string
    */
    protected $model = \App\Models\Post::class;
    /**
     * Define the model's default state.
     *
     * @return array
     */
  

    public function definition()
    {
        return [
            'body' => $this->faker->text($maxNbChars = 200),
            'user_id' => $this->faker->randomElement(User::get())->id,
         
        ];
    }
}
