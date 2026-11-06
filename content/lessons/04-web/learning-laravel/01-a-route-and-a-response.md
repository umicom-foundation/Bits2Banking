# A route and a response

[Course contents](index.md) · [Next: A view with data](02-a-view-with-data.md)

## Give a request somewhere to go

Complete Learning PHP's functions and Learning HTML's links first. A browser sends an HTTP request. A route matches its method and path to application code. A response supplies a status and content. A route is not the same as a file path on disk.

This introductory exercise uses a Laravel 12 project deliberately, so its source conventions are explicit. It is not a claim that 12 is the newest release. Follow the official version-specific installation prerequisites for PHP, Composer and extensions. In an empty parent practice folder run:

```text
composer create-project laravel/laravel learning-portal "^12.0"
cd learning-portal
php artisan --version
```

Composer downloads dependencies; `artisan` is the project's command-line entry. Do not continue after an installation failure. Record the selected framework version and retain its lock file.

## Add one route

Open `routes/web.php`. Keep its existing routes and PHP opening tag. Add this declaration after the imports:

```php
Route::get('/learning', function () {
    return 'Welcome to the learning library';
});
```

The standard file imports `Illuminate\Support\Facades\Route`; verify that import exists. `get` handles a GET request. The anonymous function runs when that route is requested, and returns the response text.

Run `php artisan serve --host=127.0.0.1 --port=8000`. Open `http://127.0.0.1:8000/learning`. Expect the welcome sentence. Stop the development server with Ctrl+C when finished. A 404 means the requested path was not matched; check the URL, file and route listing with `php artisan route:list` before editing unrelated code.

## Exercise and answer

Add a separate `/learning/help` route returning `Choose one course and follow its order`. Visit both URLs and an unregistered URL. Expect two intended responses and a not-found response. That is evidence of routing, not a complete course database.

Compare the static Bits2Banking HTML course index: a static file can be served without a PHP route. Use a backend when a workflow actually needs server behaviour, and keep reusable Umicom business rules in Framework rather than duplicating them in route closures.

[Review the prerequisite course](../../../courses/learning-php/index.html).


## Source and further reading

[Read the related Umicom example](../../../courses/learning-html/index.html). Path: `content/courses/learning-html/index.html`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://laravel.com/framework/docs/12.x/routing). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-laravel/lessons/01-a-route-and-a-response.html).

[Course contents](index.md) · [Next: A view with data](02-a-view-with-data.md)

Sammy Hegab · Umicom Foundation · Original learning material.
