#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include "../glftRenderString.h"

int main(int argc, char** argv) {
    // Argumente prüfen
    if (argc < 5) {
        printf("Usage: %s <string> <duration> <font> <color (r,g,b)> <mode>\n", argv[0]);
        return 1;
    }

    const char* text = argv[1];
    int duration = atoi(argv[2]);
    char* font = argv[3];

    // Farbe verarbeiten
    float r, g, b;
    sscanf(argv[4], "%f,%f,%f", &r, &g, &b); // Beispiel: "1.0,0.0,0.0" für rot

    // GLFW initialisieren
    if (!glfwInit()) {
        return -1;
    }

    // Fenster-Attribute setzen
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    // Fenster erstellen
    GLFWwindow* window = glfwCreateWindow(1, 1, "Informer", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Font laden
    glftFont* fontname = glftLoadFont(font, 48);
    if (!fontname) {
        printf("Fehler beim Laden der Schriftart\n");
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    glftSetCurrentFont(fontname);

    // Messen der String-Größe
    int textWidth = glftMeasureString(text, 1.0f);
    int textHeight = 48; // Höhe aus der Schriftstruktur

    // Fenstergröße anpassen
    glfwSetWindowSize(window, textWidth, textHeight);

    // Fenster zentrieren
    int monitorCount;
    GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
    GLFWmonitor* primaryMonitor = monitors[0];
    const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

    int xPos = (mode->width - textWidth) / 2;
    int yPos = (mode->height - textHeight) / 2;
    glfwSetWindowPos(window, xPos, yPos);
    glfwShowWindow(window);

    // Starte die Zeitmessung
    double startTime = glfwGetTime();
    double fadeDuration = duration / 2.0; // Fade in und out in der Hälfte der Zeit

    // Rendering-Loop
    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        if ((currentTime - startTime) * 1000.0 > duration) {
            break; // Beende die Schleife, wenn die Zeit abgelaufen ist
        }

        // Fading
        double elapsed = (currentTime - startTime) * 1000.0f;
        float alpha;

        if (elapsed < fadeDuration) {
            alpha = (float)(elapsed / fadeDuration); // Fade in
        } else if (elapsed < duration - fadeDuration) {
            alpha = 1.0f; // Vollständig sichtbar
        } else {
            alpha = (float)((duration - elapsed) / fadeDuration); // Fade out
        }

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Hintergrundfarbe
        glClear(GL_COLOR_BUFFER_BIT);

        int win_width, win_height;
        glfwGetFramebufferSize(window, &win_width, &win_height);
        glViewport(0, 0, win_width, win_height); // Setze den Viewport

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, win_width, win_height, 0, 0, 1); // Orthographische Projektion

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity(); // Modelview zurücksetzen

        // Blending aktivieren
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Blending-Funktion aktivieren

        glDisable(GL_DEPTH_TEST);
 
 
        glftRenderText(text, 0, textHeight / 2, 1.0f, r, g, b, (int)(alpha * (float)255)); // Weißer Text mit Alpha

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glftCleanup();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
