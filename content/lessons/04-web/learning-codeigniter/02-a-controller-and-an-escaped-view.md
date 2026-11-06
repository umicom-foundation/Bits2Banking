# A controller and an escaped view

[Course contents](index.md) · [Previous: An explicit route](01-an-explicit-route.md)

## Give presentation its own file

Continue in the project from lesson 1. A view contains the HTML presentation. The controller supplies data and returns the rendered result. This makes it easier to change the page layout without changing route selection.

Create `app/Views/course.php`:

```php
<!doctype html>
<html lang="en">
<meta charset="utf-8">
<title>Course overview</title>
<main>
  <h1><?= esc($title) ?></h1>
  <p>Begin with the first lesson and check its expected result.</p>
</main>
</html>
```

Add a method to the existing Learning controller, inside its class:

```php
public function course(): string
{
    return view('course', ['title' => 'Learning HTML & CSS']);
}
```

Add a route to `app/Config/Routes.php`:

```php
$routes->get('learning/course', 'Learning::course');
```

The array maps title to its text. `view` selects the template. `esc` encodes the value for its default HTML output context. The short echo syntax `<?= ... ?>` outputs that encoded value. It does not run a second HTTP request.

## Observe the complete path

Start the local development server as before and visit `/learning/course`. Expect the heading Learning HTML & CSS. Then change the title to `Learning <C>` and reload. Expect literal angle brackets in the heading rather than a new HTML element.

```text
GET /learning/course -> route -> controller data -> view -> response
```

## Exercise

In a practice copy, change `view('course', ...)` to `view('missing_course', ...)` without creating another view file. Reload the page. Which step of the request path fails? Restore `course` and reload again.

## Explained answer

The route still selects the controller, but rendering cannot find `app/Views/missing_course.php`. The page cannot be completed. Restoring the view name restores the connection to the existing template. A successful route match is not enough: its downstream dependencies must exist too. Keep detailed diagnostics local while learning; production error handling must avoid disclosing private configuration.

Compare this with Bits2Banking's manifest and HTML pairs. A course's order is data that must agree with its navigation. When a later integration reads Umicom course metadata, it should consume that declared order rather than invent another sort. The exercise adds no database or login yet; those belong after request flow and output handling are understood.

[Review the prerequisite course](../../../courses/learning-php/index.html).


## Source and further reading

[Read the related Umicom example](../../../courses/learning-php/index.html). Path: `content/courses/learning-php/index.html`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://codeigniter.com/user_guide/guides/first-app/static_pages.html). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-codeigniter/lessons/02-a-controller-and-an-escaped-view.html).

[Course contents](index.md) · [Previous: An explicit route](01-an-explicit-route.md)

Sammy Hegab · Umicom Foundation · Original learning material.
