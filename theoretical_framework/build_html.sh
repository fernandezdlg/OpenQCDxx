#!/bin/bash

# Try to remove the html directory if it exists
if [ -d "html" ]; then
    rm -r html
fi

# Create a new html directory
mkdir html

# Loop through all Markdown files in the current directory
for mdfile in *.md; do
    # Get the base name of the file (without extension)
    base_name=$(basename "$mdfile" .md)

    # Convert the Markdown file to HTML
    pandoc "$mdfile" -o "html/${base_name}.html"

    # Add the Skeleton CSS link to the HTML file
    sed -i '' '1i\
    <!DOCTYPE html>\
    <html>\
    <head>\
    <link rel="stylesheet" href="../css/skeleton.css">\
    </head>\
    <body>
    ' "html/${base_name}.html"
    echo '</body></html>' >> "html/${base_name}.html"
done

echo "Conversion complete for all Markdown files in the directory."
