# A view with data

[Course contents](index.md) · [Previous: A route and a response](01-a-route-and-a-response.md)

## Separate page structure from request handling

Continue with the same Laravel project. A view is a presentation template. Blade is Laravel's template language. The controller or route chooses data; the view decides how to present it. This separation keeps a long HTML page out of request-dispatch code.

Create `resources/views/lesson.blade.php`:

```html
<!doctype html>
<html lang="en">
<meta charset="utf-8">
<title>Learning library</title>
<main>
  <h1>{{ $title }}</h1>
  <p>Read the example, predict its result, then practise.</p>
</main>
</html>
```

Add a new route to `routes/web.php`, preserving the previous lesson's routes:

```php
Route::get('/learning/first-lesson', function () {
    return view('lesson', ['title' => 'Learning C & GTK4']);
});
```

`view('lesson', ...)` resolves the template's logical name; it is not an arbitrary user-supplied filename. The array associates the key title with a value made available as `$title`. Double braces escape normal text output.

Start the local server as before and visit `/learning/first-lesson`. Expect the heading Learning C & GTK4. If Laravel cannot find the view, compare its name with the file path and extension. If title is undefined, check the data key and variable spelling.

## Exercise and answer

Change the title value to `Learning <C> & GTK4` and reload. The angle brackets should appear as text. Do not switch to raw HTML output to make ordinary text display; that changes the trust boundary. Add a second paragraph of your own explanation and confirm it appears without changing the route.

## Connect to Umicom

Compare a Bits2Banking course index and its `course.json`. The manifest carries ordered course data, while the HTML presents navigation. A future web service can follow that separation without becoming a second source of truth for course ordering or Framework rules. The two routes here do not store learner progress, authenticate users or install a Studio module. Those features require explicit data models, permissions and tests, and are later topics in the course outline.

[Review the prerequisite course](../../../courses/learning-php/index.html).


## Source and further reading

[Read the related Umicom example](../../../courses/learning-html/index.html). Path: `content/courses/learning-html/index.html`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://laravel.com/framework/docs/12.x/routing). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-laravel/lessons/02-a-view-with-data.html).

[Course contents](index.md) · [Previous: A route and a response](01-a-route-and-a-response.md)

Sammy Hegab · Umicom Foundation · Original learning material.
