# -----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: hooks/active_markup.py
#
# PURPOSE:
#   Keep publication metadata decisions outside inert HTML and embedded examples.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
# -----------------------------------------------------------------------------
"""HTML context admission shared by the MkDocs branding and theme observers.

Python is required by MkDocs. This helper observes markup context only; it does
not render CSS, execute scripts or determine whether a browser paints an image.
"""


class ActiveMarkup:
    """Exclude templates, conditional noscript and raw/RCDATA text containers.

    HTMLParser handles script/style as raw text, but other HTML text containers
    can still produce apparent start tags. Keep their contents as source text.
    Nested templates are counted; a template-looking string inside textarea
    cannot close or open a real template. Treat noscript conservatively because
    its contents do not appear in every supported browser configuration.
    """
    TEXT_CONTAINERS = frozenset({
        'title', 'textarea', 'script', 'style', 'xmp', 'iframe',
        'noembed', 'noframes', 'noscript',
    })

    def __init__(self):
        self.template_depth = 0
        self.text_container = None

    def outside_text(self):
        return self.template_depth == 0 and self.text_container is None

    def start(self, tag):
        if self.text_container is not None:
            return False
        if tag in self.TEXT_CONTAINERS:
            self.text_container = tag
            return False
        if tag == 'template':
            self.template_depth += 1
            return False
        return self.template_depth == 0

    def end(self, tag):
        if self.text_container is not None:
            if tag != self.text_container:
                return False
            self.text_container = None
            # An actual title end can still anchor an implicit document head.
            return self.template_depth == 0
        if tag == 'template':
            self.template_depth = max(0, self.template_depth - 1)
            return False
        return self.template_depth == 0
