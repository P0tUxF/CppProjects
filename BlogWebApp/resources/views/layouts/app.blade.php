<!DOCTYPE html>
<html lang="en">
    <head>
         <meta charset="UFT-8">
         <meta name="viewport" content="width=device-width, initial-scale=1.0">
         <meta http-equiv="X-UA-Compatible" content="ie=edge">
         <title>The Grid</title>
         <link rel="stylesheet" href="{{ asset('css/app.css') }}">
    </head>
    <body class="bg-gray-700">
        <nav class="p-6 bg-blue-600 flex justify-between mb-6">
            <ul class="flex items-center">

                <li>
                    <a href=""class="p-3 text-white font-bold hover:text-green-300 transition">The Grid</a> 
                </li>
                <li>
                    <a href="/"class="p-3 text-black font-bold hover:text-green-300 transition">Home</a> 
                </li>
                <li>
                    <a href="{{ route('dashboard')}}"class="p-3 text-black font-bold hover:text-green-300 transition">Dashboard</a> 
                </li>
                <li>
                    <a href="{{ route('posts')}}"class="p-3 text-black font-bold hover:text-green-300 transition">Post</a> 
                </li>
            </ul>
            <ul class="flex items-center">
                @auth
                    <li>
                        <a href=""class="p-3 text-black font-bold hover:text-green-300 transition">{{ auth()->user()->name }}</a> 
                    </li>
                    <li>
                        <form action="{{ route('logout')}}" method="post" class="p-3 inline">
                            @csrf
                        <button type="submit" class="text-black font-bold hover:text-green-300 transition">Logout</button> 
                    </li>
                @endauth

                @guest
                    <li>
                        <a href="{{ route('login') }}"class="p-3 text-black font-bold hover:text-green-300 transition">Login</a> 
                    </li>
                    <li>
                        <a href="{{ route('register') }}"class="p-3 text-black font-bold hover:text-green-300 transition">Register</a> 
                    </li>
                @endguest
                
                
            </ul>
        </nav>
        @yield('content')
    </body>
</html>