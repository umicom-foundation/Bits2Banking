# Output context and readable text

[Course contents](index.md) · [Previous: Frameworks, packages and Laminas](01-frameworks-packages-and-laminas.md)

## A title should remain a title

Continue in the same component exercise. HTML gives special meanings to characters such as `<` and `&`. Escaping represents text so the browser reads it as text in the intended context. It is different from validating a business value or checking whether a user may perform an action.

Save this as `page.php` beside `escape.php`:

```php
<?php
require __DIR__ . '/vendor/autoload.php';
$escaper = new Laminas\Escaper\Escaper('utf-8');
$title = 'Learning <C> & GTK4';
?>
<!doctype html>
<html lang="en">
<meta charset="utf-8">
<title>Practice lesson</title>
<main><h1><?= $escaper->escapeHtml($title) ?></h1></main>
</html>
```

Start `php -S 127.0.0.1:8000` in the practice folder and open `http://127.0.0.1:8000/page.php`. This is a local development server, not deployment configuration. Stop it with Ctrl+C when finished. Expect the heading to visibly include `<C>` and `&`. Viewing the response source should show encoded characters in the heading.

## Choose the correct operation

The example places a title between HTML tags. An HTML attribute, JavaScript string, CSS value and URL are different contexts. Laminas supplies distinct escaping operations for them. Do not take `escapeHtml` as a universal protection function or insert a title directly into script code.

## Exercise and answer

Change the title to `A & B <notes>` and reload. Expect those characters to appear as ordinary title text. If the browser interprets `<notes>` as markup, inspect whether the escaped value or the original value was output.

## Relate it to Umicom

Bits2Banking contains both Markdown and HTML views of lessons. Code examples must remain visible as examples, not become executable page markup. The same separation matters when a Framework service produces text that a web client displays: storage, validation and output representation have distinct responsibilities. A transport or UI adapter must not assume trusted formatting simply because the data came from another application. Later modules introduce request handling and dependency injection only after this small rendering boundary is understood.

[Review the prerequisite course](../../../courses/learning-php/index.html).


## Source and further reading

[Read the related Umicom example](../../../courses/learning-php/index.html). Path: `content/courses/learning-php/index.html`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://getlaminas.org/about/). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-zend-framework/lessons/02-output-context-and-readable-text.html).

[Course contents](index.md) · [Previous: Frameworks, packages and Laminas](01-frameworks-packages-and-laminas.md)

Sammy Hegab · Umicom Foundation · Original learning material.
