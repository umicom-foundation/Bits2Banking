# An explicit route

[Course contents](index.md) · [Next: A controller and an escaped view](02-a-controller-and-an-escaped-view.md)

## Name the path and its handler

First complete the PHP and HTML foundations. CodeIgniter 4 is a PHP web framework. Its route configuration maps a request to a controller method. A controller coordinates a request; it should not become the storage location for every business rule.

Install PHP and Composer according to CodeIgniter 4's current requirements, including the listed PHP extensions. In a practice parent folder, run:

```text
composer create-project codeigniter4/appstarter learning-portal
cd learning-portal
php spark --version
```

Stop on installation errors. `spark` is this project's command-line tool. Keep `composer.lock` so later work can identify the dependencies used in the exercise.

Create `app/Controllers/Learning.php`:

```php
<?php
namespace App\Controllers;

class Learning extends BaseController
{
    public function index(): string
    {
        return 'Choose a learning course';
    }
}
```

Add to `app/Config/Routes.php`, keeping its existing content:

```php
$routes->get('learning', 'Learning::index');
```

The first string is the URL path; the second names the controller and method. Explicit routing makes the intended entry visible. It does not depend on automatically exposing every public method.

Run `php spark serve --host 127.0.0.1 --port 8080` and visit `http://127.0.0.1:8080/learning`. Expect the course-selection sentence. Stop the server with Ctrl+C afterward. If the route is missing, inspect `php spark routes` and check controller filename, class name and namespace together.

## Exercise and answer

Add a separate `help` method returning a short sentence and an explicit `learning/help` route. Verify the original route still works. If only the second route works, you may have overwritten rather than extended the file.

Relate this to a Studio menu event: there must be an identifiable path from input to handler. A visible label alone does not establish wiring. These PHP pages are an independent learning exercise; no native Framework integration is implied by the shared lesson topic.

[Review the prerequisite course](../../../courses/learning-php/index.html).


## Source and further reading

[Read the related Umicom example](../../../courses/learning-php/index.html). Path: `content/courses/learning-php/index.html`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://codeigniter.com/user_guide/guides/first-app/static_pages.html). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-codeigniter/lessons/01-an-explicit-route.html).

[Course contents](index.md) · [Next: A controller and an escaped view](02-a-controller-and-an-escaped-view.md)

Sammy Hegab · Umicom Foundation · Original learning material.
