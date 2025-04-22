// --------------------------------------------------------------------------
// gMini,
// a minimal Glut/OpenGL app to extend                              
//
// Copyright(C) 2007-2009                
// Tamy Boubekeur
//                                                                            
// All rights reserved.                                                       
//                                                                            
// This program is free software; you can redistribute it and/or modify       
// it under the terms of the GNU General Public License as published by       
// the Free Software Foundation; either version 2 of the License, or          
// (at your option) any later version.                                        
//                                                                            
// This program is distributed in the hope that it will be useful,            
// but WITHOUT ANY WARRANTY; without even the implied warranty of             
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              
// GNU General Public License (http://www.gnu.org/licenses/gpl.txt)           
// for more details.                                                          
//                                                                          
// --------------------------------------------------------------------------

uniform float ambientRef;
uniform float diffuseRef;
uniform float specularRef;
uniform float shininess;
uniform int levels;

varying vec4 p;
varying vec3 n;

void main (void) {
    vec3 P = vec3 (gl_ModelViewMatrix * p);
    vec3 N = normalize(gl_NormalMatrix * n); // Normal normalisée
    vec3 L = normalize(gl_LightSource[0].position.xyz - P); // Direction de la lumière
    vec3 V = normalize(-P); // Vecteur de vue
    L = V;

    float dotLN = max(dot(N, L), 0.0);
    float stepSize = 1.0 / float(levels);
    float diffuse = floor(dotLN / stepSize) * stepSize;

    vec4 color = gl_FrontMaterial.diffuse * diffuse; // Application du shading

    float edgeThreshold = 0.3; // contour noir
    if (dot(N, V) < edgeThreshold) {
        color = vec4(0.0, 0.0, 0.0, 1.0); // Noir si proche du bord
    }

    gl_FragColor = color;

    // vec3 P = vec3 (gl_ModelViewMatrix * p); //Position du point à éclairer
    // vec3 N = normalize (gl_NormalMatrix * n); //Normal en ce point
    // vec3 V = normalize (-P); //Vecteur de vue
    
    // vec4 Isa = gl_LightModel.ambient;
    // vec4 Ka = gl_FrontMaterial.ambient;
    // vec4 Ia = Isa * Ka;

    // vec4 I = ambientRef * Ia ;

    // const int NUM_Lights = 8;

    // for (int i = 0; i < NUM_Lights; i++){
    //     if (gl_LightSource[i].diffuse == vec4(0.0) && gl_LightSource[i].specular == vec4((0.0))){
    //         continue;
    //     }

    // vec4 Isd = gl_LightSource[i].diffuse;
    // vec4 Kd = gl_FrontMaterial.diffuse;

    // vec3 L = normalize(gl_LightSource[i].position.xyz - P);
    // float cosThe = max(dot(N, L), 0.0);
    // vec4 Id = diffuseRef * Kd * Isd * cosThe;

    // I += Id;

    // vec4 Iss = gl_LightSource[i].specular;
    // vec4 Ks = gl_FrontMaterial.specular;
    // vec3 R = 2.0 * cosThe * N - L;
    // float cosAlpha = max(dot(R,V),0.0);

    // vec4 Is = specularRef * Iss * Ks * pow(cosAlpha,shininess);

    // I += Is;

    // }


    ////////////////////////////////////////////////
    //Eclairage de Phong à calculer en utilisant
    ///////////////////////////////////////////////
    // gl_LightSource[i].position.xyz Position de la lumière i
    // gl_LightSource[i].diffuse Couleur diffuse de la lumière i
    // gl_LightSource[i].specular Couleur speculaire de la lumière i
    // gl_FrontMaterial.diffuse Matériaux diffus de l'objet
    // gl_FrontMaterial.specular Matériaux speculaire de l'objet


    //gl_FragColor =vec4 (I.xyz, 1);
}

