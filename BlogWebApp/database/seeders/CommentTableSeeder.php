<?php

namespace Database\Seeders;
use App\Models\Comment;
use Illuminate\Database\Seeder;

class CommentTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *d
     * @return void
     */
    public function run()
    {
        $c = new Comment;
        //$c->post_id = 1;
        $c->reply = "Interesting caption!";
        $c->user_id = 1;
        $c->save();
        $comment = Comment::factory()->count(10)->create();
    }
}
