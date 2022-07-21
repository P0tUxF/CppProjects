@extends('layouts.app')

@section('content')
<div class="flex justify-center">
    <div class="w-8/12 bg-blue-600 p-6 rounded-lg">
        <form action="{{ route('posts')}}" method="post" class="mb-4">
            @csrf
            <div class="mb-4">
                <label for="body" class="sr-only">Body</label>
                <textarea name="body" id="body" cols="30" rows="4" class="bg-gray-100
                border-2 w-full p-4 rounded lg @error('body') border-red-500 @enderror"
                placeholder="Post something dudee"></textarea>

                @error('body')
                    <div class="text-red-500 mt-2 text-sm">
                        {{ $message }}
                    </div>
                @enderror

                <button type="submit" class="bg-gray-700 text px-4 py-2 rounded
                font-medium text-white">Post</button>
            </div>
        </form>

        @if($posts->count())
            @foreach ($posts as $post)
                <div class="mb-4">
                    <a href="" class="font-bold">{{ $post->user->name }}</a><span class="text-gray-600 text-sm">
                        {{ $post->created_at->diffForHumans() }}</span>

                    <p class="mb-2">{{ $post->body }}</p>
                    
                    @if($post->ownedBy(auth()->user()))
                        <div>
                            <form action="{{ route('posts', $post) }}" method="post">
                                @csrf
                                @method('DELETE')
                                <button type="submit" class="text-green-300">Delete</button>
                            </form>
                        </div>
                    @endif
                </div>



                <div class="flex items-center">
                    <form action="{{ route('posts.likes', $post->id) }}" method="post" class="mr-1">
                        @csrf
                        <button type="submit" class="text-green-300">Like</button>
                    </form>
                    <form action="" method="post" class="mr-1">
                        @csrf
                        <button type="submit" class="text-green-300">Dislike</button>
                    </form>
    
                    <span>{{ $post->likes->count() }} {{ Str::plural('like', $post->likes->count())
                     }}</span>
                </div>
            @endforeach

            {{ $posts->links() }}

        @else
            <p> There are 0 posts</p>
        @endif
    </div>
</div>
@endsection
