#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <cmath> // Voor tanf()

// Vervanging van gluPerspective
void setPerspective(float fov, float aspect, float near, float far) {
    float radians = fov * 3.141592653589793f / 180.0f; // Converteer graden naar radians
    float top = near * tanf(radians / 2.0f);
    float bottom = -top;
    float right = top * aspect;
    float left = -right;

    glFrustum(left, right, bottom, top, near, far); // Stel de frustum in
}

int main() {
    // Maak een SFML-venster
    sf::Window window(sf::VideoMode(800, 600), "3D Rotating Cube", sf::Style::Default, sf::ContextSettings(24));
    window.setActive(true);

    // OpenGL-instellingen
    glEnable(GL_DEPTH_TEST); // Activeer dieptebuffer
    glEnable(GL_COLOR_MATERIAL); // Activeer kleurmateriaal

    float rotation = 0.0f; // Rotatiehoek

    // Hoofdprogramma-lus
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Wis het scherm en de dieptebuffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Stel de projectiematrix in
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        setPerspective(45.0f, 800.0f / 600.0f, 1.0f, 100.0f); // Gebruik vervanging voor gluPerspective

        // Stel de model-/viewmatrix in
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -6.0f); // Verplaats de kubus naar achteren
        glRotatef(rotation, 1.0f, 1.0f, 0.0f); // Draai de kubus

        // Teken een eenvoudige 3D-kubus
        glBegin(GL_QUADS);

        // Voorzijde
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);

        // Achterzijde
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(1.0f, 1.0f, -1.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);

        // Andere zijden...

        glEnd();

        // Update rotatiehoek
        rotation += 0.5f;

        // Toon het venster
        window.display();
    }

    return 0;
}
