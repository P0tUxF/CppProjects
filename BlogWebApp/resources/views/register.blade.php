@extends('layouts.app')

@section('content')
<div class="flex justify-center">
    <div class="w-4/12 bg-blue-600 p-6 rounded-lg">
        <form action="{{ route('register') }}" method="post">
            @csrf
            <div class="mb-4">
                <label for="name" class="sr-only">Name</label>
                <input type="text" name="name" id="name" placeholder="Name"
                class="bg-gray-100 border-2 w-full p-4 rounded-lg @error('name') border-red-500 @enderror" value="{{old('name')}}">
                @error('name')
                <div class="text-red-700 mt-2 text-sm">
                    {{ $message }}
                </div>
                @enderror
            </div>

            <div class="mb-4">
                <label for="username" class="sr-only">Username</label>
                <input type="text" name="username" id="username" placeholder="Username"
                class="bg-gray-100 border-2 w-full p-4 rounded-lg @error('username') border-red-500 @enderror" value="{{old('username')}}">
                @error('username')
                <div class="text-red-700 mt-2 text-sm">
                    {{ $message }}
                </div>
                @enderror
            </div>


            <div class="mb-4">
                <label for="email" class="sr-only">Email</label>
                <input type="text" name="email" id="email" placeholder="Email"
                class="bg-gray-100 border-2 w-full p-4 rounded-lg @error('email') border-red-500 @enderror" value="{{old('email')}}">
                @error('email')
                <div class="text-red-700 mt-2 text-sm">
                    {{ $message }}
                </div>
                @enderror
            </div>

            <div class="mb-4">
                <label for="password" class="sr-only">Password</label>
                <input type="password" name="password" id="password" placeholder="Password"
                class="bg-gray-100 border-2 w-full p-4 rounded-lg @error('password') border-red-500  @enderror" value="">
                @error('password')
                <div class="text-red-700 mt-2 text-sm">
                    {{ $message }}
                </div>
                @enderror
            </div>

            <div class="mb-4">
                <label for="password_confirmation" class="sr-only">Retype Password</label>
                <input type="password" name="password_confirmation" id="password_confirmation" 
                placeholder ="Retype Password" class="bg-gray-100 border-2 w-full p-4 rounded-lg" value="">
            </div>
            
                <button type="submit" class="bg-gray-700 text px-4 py-3 rounded
                font-medium w-full text-white">Register</button>
        </form>
    </div>

</div>
@endsection

