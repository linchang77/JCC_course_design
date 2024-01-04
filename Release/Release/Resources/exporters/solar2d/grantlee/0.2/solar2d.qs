
var ExportAnimations = function(root)
{
    if (root.animations.length == 0)
    {
        return "";
    }

    var spriteIndicesByName = {};
    for (let i = 0; i < root.allSprites.length; i++)
    {
        spriteIndicesByName[root.allSprites[i].trimmedName] = i+1;
    }

    var output = "\n";
    output += "SheetInfo.animation = \n";
    output += "{\n";
    for (let i = 0; i < root.animations.length; i++)
    {
        const anim = root.animations[i];

        output += i ? ",\n" : ""
        output += "   [\"";
        output += anim.name;
        output += "\"] = { ";

        for (let j = 0; j < anim.frames.length; j++)
        {
            const frame = anim.frames[j];
            output += j ? ", " : "";
            output += spriteIndicesByName[frame.trimmedName];
        }
        output += " }";
    }
    output += "\n}\n";

    return output;
}

ExportAnimations.filterName = "ExportAnimations";
Library.addFilter("ExportAnimations");


