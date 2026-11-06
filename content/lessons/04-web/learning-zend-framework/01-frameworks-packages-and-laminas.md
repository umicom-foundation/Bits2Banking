# Frameworks, packages and Laminas

[Course contents](index.md) · [Next: Output context and readable text](02-output-context-and-readable-text.md)

## Keep the history clear

Begin after Learning PHP and Learning HTML. A library supplies reusable operations. A framework also provides conventions for arranging an application and connecting those operations. A package is a distributable unit with dependency information. Composer is a PHP dependency manager that downloads compatible packages and records selected versions.

Zend Framework's open-source continuation is Laminas. This course keeps the requested Learning Zend Framework title for historical continuity, but new exercises use named Laminas components. That does not mean every old Zend application can be upgraded by replacing a word. Check the maintenance status and migration guide for each component before a real migration.

## Create an isolated component exercise

With PHP and Composer installed, choose an empty practice folder. Run:

```text
php --version
composer --version
composer require laminas/laminas-escaper
```

Stop if dependency installation fails. Composer explains incompatible PHP versions or missing extensions. Do not bypass those requirements. Inspect `composer.json`, `composer.lock` and the `vendor` directory. The first describes requirements; the lock records resolved versions; vendor contains installed dependencies.

Save this as `escape.php`:

```php
<?php
require __DIR__ . '/vendor/autoload.php';
$escaper = new Laminas\Escaper\Escaper('utf-8');
echo $escaper->escapeHtml('C < C++ & GTK4'), PHP_EOL;
```

Run `php escape.php`. Expect entity text equivalent to `C &lt; C++ &amp; GTK4`. `__DIR__` refers to the script's directory, avoiding dependence on the terminal's current folder when locating its dependency loader. The backslashes separate namespace parts, not filesystem folders in this expression.

## Exercise and answer

Change the title to `Notes & lessons`. Expect the ampersand to be encoded. The value has not been deleted or treated as a command; it has been represented for an HTML text context. The next lesson explains why output context matters.

Compare the PHP course's existing source examples with Framework's dependency-based design. Reuse is valuable because one reviewed component can serve multiple callers. This exercise does not add PHP to the native Umicom engine or claim a complete MVC application has been built.

[Review the prerequisite course](../../../courses/learning-php/index.html).


## Source and further reading

[Read the related Umicom example](../../../courses/learning-php/index.html). Path: `content/courses/learning-php/index.html`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://getlaminas.org/about/). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-zend-framework/lessons/01-frameworks-packages-and-laminas.html).

[Course contents](index.md) · [Next: Output context and readable text](02-output-context-and-readable-text.md)

Sammy Hegab · Umicom Foundation · Original learning material.
