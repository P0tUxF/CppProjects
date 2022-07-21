<?php

namespace Database\Seeders;
use App\Models\User;
use App\Models\Post;
use App\Models\Comment;
use Illuminate\Database\Seeder;

class UserTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        $u = new User;
        $u->name = "Takemichi";
        $u->username = "Hanagaki";
        $u->email = "hanagakiT@tokyo.com";
        $u->password = "hinata";
        $u->save();

      $users = User::factory()
          ->has(Post :: factory(),'posts') 
          ->has(Comment :: factory(),'comments')
          ->count(10)->create();
    }
}
