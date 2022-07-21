<?php

namespace Database\Seeders;
use App\Models\Post;
use Illuminate\Database\Seeder;

class PostTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
       $p = new Post;
       $p->body = "This is my post";
       $p->user_id = 1;
       $p->save();
       $post = Post::factory()->count(10)->create();
    }

}
