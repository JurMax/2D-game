#version 330

uniform vec2 u_screenSize;
uniform vec2 u_screenOffset;
uniform float u_screenScale;

uniform float FXAA_SUBPIX_SHIFT = 1.0/4.0;


uniform vec2 u_shapePos;
uniform float u_shapeRotation;
uniform vec2 u_shapeRotationPoint;

in vec2 vertexPos;
in vec4 vertexColor;
in vec2 vertexTexCoord;
in vec3 vertexBarycentric;

out vec4 fragmentColor;
out vec2 fragmentTexCoord;
out vec3 fragmentBarycentric;
out vec4 fragmentInObjectPos;


void main() {

    vec2 rotationPos = vertexPos - u_shapeRotationPoint;
    
    vec2 finalVertexPos;
    finalVertexPos.x = rotationPos.x * cos(u_shapeRotation) - rotationPos.y * sin(u_shapeRotation);
    finalVertexPos.y = rotationPos.y * cos(u_shapeRotation) + rotationPos.x * sin(u_shapeRotation);
    finalVertexPos += u_shapeRotationPoint;
    
    vec2 pos = (u_shapePos + finalVertexPos + u_screenOffset) / (50.0 * u_screenScale) - 1.0;
    pos.y += 1.2;
    pos.y *= u_screenSize.x / u_screenSize.y;
    gl_Position = vec4(pos.x, pos.y, 0.0, 1.0);
    
    fragmentColor = vertexColor;
    fragmentTexCoord = vertexTexCoord;
    fragmentBarycentric = vertexBarycentric;
    
    /*vec2 rcpFrame = vec2(1.0/u_screenSize.x, 1.0/u_screenSize.y);
    fragmentInObjectPos.xy = vertexTexCoord.xy;
    fragmentInObjectPos.zw = vertexTexCoord.xy - (rcpFrame * (0.5 + FXAA_SUBPIX_SHIFT));*/
}