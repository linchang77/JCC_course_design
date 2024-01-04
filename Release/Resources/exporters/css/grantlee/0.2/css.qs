let spriteHash = {};
let spriteHash2x = {};

var ExportData = function(root)
{
    let subPath = root.settings.textureSubPath;
    let spritePrefix = root.exporterProperties.sprite_prefix;

    // we only support two scaling variants
    let variant = root.allResults[0];
    let variant2x = root.allResults[1]; // might be undefined
    if (variant2x && root.settings.autoSDSettings[0].scale > root.settings.autoSDSettings[1].scale)
    {
        [variant, variant2x] = [variant2x, variant]; // swap
    }

    let result = "";
    result += spriteLines(variant, subPath, spritePrefix);
    result += animationLines(root, variant, spriteHash);

    if (variant2x)
    {
        result += "@media " + root.exporterProperties.media_query_2x + " {\n";
        result += spriteLines2x(variant2x, subPath, spritePrefix);
        result += animationLines2x(root, variant2x, spriteHash2x);
        result += "}\n\n";
    }

    return result;
}

ExportData.filterName = "exportData";
Library.addFilter("ExportData");

let makeImagePath = function(variant, multipackIndex, subPath)
{
    let imageName = variant.textures[multipackIndex].fullName;
    if(subPath)
    {
        imageName = subPath+"/"+imageName;
    }
    return imageName;
}

function backgroundPosition(texture, sprite)
{
    const divX = (texture.size.width - sprite.frameRect.width);
    let x = (divX === 0) ? 0 : 100*(sprite.frameRect.x)/divX;

    const divY = (texture.size.height - sprite.frameRect.height);
    let y = (divY === 0) ? 0 : 100*(sprite.frameRect.y)/divY;

    return "background-position: " + x + "% " + y + "%; ";
}

function backgroundSize(texture, sprite)
{
    let width = 100*texture.size.width/sprite.frameRect.width;
    let height = 100*texture.size.height/sprite.frameRect.height;
    return "background-size: " + width + "% " + height + "%; ";
}

function spriteLines(variant, subPath, spritePrefix)
{
    let lines = [];

    for (let multipackIndex = 0; multipackIndex < variant.textures.length; multipackIndex++)
    {
        let texture = variant.textures[multipackIndex];

        let imageName = makeImagePath(variant, multipackIndex, subPath);

        for (let j = 0; j < texture.allSprites.length; j++)
        {
            let sprite = texture.allSprites[j];
            spriteHash[sprite.trimmedName] = sprite;

            let cssClassName = makeSelector(sprite.trimmedName, spritePrefix);

            let line1 = cssClassName + " {"
             + "max-width:"+sprite.frameRect.width+"px; "
             + "max-height:"+sprite.frameRect.height+"px; "
             + "}";

            let ratio = 100*sprite.frameRect.height/sprite.frameRect.width;

            let line2 = cssClassName + "::after {"
                + "content: '\\00a0';"
                + "display: inline-block; "
                + "width:"+sprite.frameRect.width+"px; "
                + "height:"+sprite.frameRect.height+"px; "
                + backgroundPosition(texture, sprite)
                + backgroundSize(texture, sprite)
                + "background-image: url("+imageName+");"
                + "padding: 0; "
                + "}";

            let line3 = "div" + cssClassName + "::after {"
                + "max-width:"+sprite.frameRect.width+"px; "
                + "width:100%;"
                + "height:0;"
                + "padding: 0 0 "+ratio+"% 0;"
                + "}"

            lines.push(line1+"\n"+line2+"\n"+line3);
        }
    }

    lines.sort();

    return lines.join('\n') + '\n\n';
}

function spriteLines2x(variant, subPath, spritePrefix)
{
    let lines = [];

    for (let multipackIndex = 0; multipackIndex < variant.textures.length; multipackIndex++)
    {
        let texture = variant.textures[multipackIndex];

        let imageName = makeImagePath(variant, multipackIndex, subPath);

        for (let j = 0; j < texture.allSprites.length; j++)
        {
            let sprite = texture.allSprites[j];
            spriteHash2x[sprite.trimmedName] = sprite;

            let line = makeSelector(sprite.trimmedName, spritePrefix) + "::after {"
             + backgroundPosition(texture, sprite)
             + "background-image: url("+imageName+"); "
             + "}";

            lines.push(line);
        }
    }

    lines.sort();

    return '    '+lines.join('\n    ') + '\n';
}

function animationLines(root, variant, spriteHash)
{
    let lines = [];
    const texture = variant.textures[0];
    for (let i = 0; i < root.animations.length; i++)
    {
        const anim = root.animations[i];
        const animName = root.exporterProperties.sprite_prefix + escapeString(anim.name) + "-frames";

        lines.push("@keyframes " + animName + " {");
        for (let j = 0; j < anim.frames.length; j++)
        {
            let progress = (j / anim.frames.length) * 100;
            let sprite = spriteHash[anim.frames[j].trimmedName];

            lines.push("    " + progress + "% { " + backgroundPosition(texture, sprite) + " }");
        }
        lines.push("}");
        lines.push("");

        const selector = makeSelector(anim.name, root.exporterProperties.sprite_prefix) + "-animation";
        const imgFile = makeImagePath(variant, 0, root.settings.textureSubPath);
        const sprite = spriteHash[anim.frames[0].trimmedName];
        const size = sprite.size;
        let ratio = 100*sprite.frameRect.height/sprite.frameRect.width;

        lines.push(selector + " {");
        lines.push("    max-width: " + size.width + "px;");
        lines.push("    max-height: " + size.height + "px;");
        lines.push("}");

        lines.push(selector + "::after {");
        lines.push("    content: '\\00a0';");
        lines.push("    display: inline-block;");
        lines.push("    width: " + size.width + "px;");
        lines.push("    height: " + size.height + "px;");
        lines.push("    padding: 0;");
        lines.push("    background-image: url(" + imgFile + ");");
        lines.push("    " + backgroundSize(texture, sprite));
        lines.push("    animation-name: " + animName + ";");
        lines.push("    animation-timing-function: steps(1);");
        lines.push("    animation-duration: 1s;");
        lines.push("    animation-iteration-count: infinite;");
        lines.push("}");

        lines.push("div" + selector + "::after {");
        lines.push("    max-width: " + size.width + "px;");
        lines.push("    width: 100%;");
        lines.push("    height: 0;");
        lines.push("    padding: 0 0 " + ratio + "% 0;");
        lines.push("}");
        lines.push("");
    }

    return lines.join('\n') + '\n';
}

function animationLines2x(root, variant, spriteHash)
{
    const texture = variant.textures[0];
    const imgFile = makeImagePath(variant, 0, root.settings.textureSubPath);
    let lines = [];

    for (let i = 0; i < root.animations.length; i++)
    {
        const anim = root.animations[i];
        const selector = makeSelector(anim.name, root.exporterProperties.sprite_prefix) + "-animation";
        const sprite = spriteHash[anim.frames[0].trimmedName];
        lines.push("");
        lines.push("    " + selector + "::after {");
        lines.push("        background-image: url(" + imgFile + ");");
        lines.push("        " + backgroundSize(texture, sprite));
        lines.push("    }");
    }
    return lines.join('\n') + '\n';
}

function escapeString(input) {
    input = input.replace(/\//g, "-");
    input = input.replace(/\\/g, "-");
    input = input.replace(/\s+/g, "-");
    return input;
}

function makeSelector(input, spritePrefix)
{
    input = escapeString(input);
    input = input.replace(/-link/,":link");
    input = input.replace(/-visited/,":visited");
    input = input.replace(/-focus/,":focus");
    input = input.replace(/-active/,":active");
    input = input.replace(/-hover/,":hover");

    return "."+spritePrefix+input;
}
