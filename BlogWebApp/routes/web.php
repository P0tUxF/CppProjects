<?php

use Illuminate\Support\Facades\Route;
use App\Http\Controllers\RegisterController;
use App\Http\Controllers\DashboardController;   
use App\Http\Controllers\LoginController;   
use App\Http\Controllers\LogoutController;   
use App\Http\Controllers\PostController;   
use App\Http\Controllers\PostLikeController;   



        Route::get('/', function() 
        {
        return view('home');
        }) ->name('home');

        Route::get('/register', [RegisterController::class, 'index'])->name('register'); 
        Route::post('/register', [RegisterController::class, 'store']);
        
        Route::post('/logout', [LogoutController::class, 'store'])->name('logout');  

        Route::get('/dashboard', [DashboardController::class, 'index'])->name('dashboard');

        Route::get('/login', [LoginController::class, 'index'])->name('login'); 
        Route::post('/login', [LoginController::class, 'store']);

        
        Route::get('/posts', [PostController::class, 'index'])->name('posts');
        Route::post('/posts', [PostController::class, 'store']);
        Route::delete('/posts/{post}', [PostController::class, 'destroy']);

        Route::post('/posts/{id}/likes', [PostLikeController::class, 'store'])->name('posts.likes');
