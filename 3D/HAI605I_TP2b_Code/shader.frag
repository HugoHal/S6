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
    vec3 P = vec3(gl_ModelViewMatrix * p);
    vec3 N = normalize(gl_NormalMatrix * n); // Normal normalisée
    vec3 L = normalize(gl_LightSource[0].position.xyz - P); // Direction de la lumière
    vec3 V = normalize(-P); // Vecteur de vue

    // Calcul du vecteur de demi-angle
    vec3 H = normalize(L + V);

    // Composant diffus
    float dotLN = max(dot(N, L), 0.0);
    vec4 Id = diffuseRef * gl_LightSource[0].diffuse * gl_FrontMaterial.diffuse * dotLN;

    // Composant spéculaire (Blinn-Phong)
    float cosAlpha = max(dot(N, H), 0.0);
    vec4 Is = specularRef * gl_LightSource[0].specular * gl_FrontMaterial.specular * pow(cosAlpha, shininess);

    // Couleur finale
    vec4 color = Id + Is;

    // Application d'un seuil pour les contours (optionnel)
    float edgeThreshold = 0.3;
    if (dot(N, V) < edgeThreshold) {
        color = vec4(0.0, 0.0, 0.0, 1.0); // Noir si proche du bord
    }

    gl_FragColor = color;
}

