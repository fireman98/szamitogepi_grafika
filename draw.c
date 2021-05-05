#include "draw.h"
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

double room_size = 200;
GLuint displayList1;
GLuint displayList2;
GLuint boxList;

void draw_model(const struct Model *model)
{
    draw_triangles(model);
    draw_quads(model);
}

void draw_triangles(const struct Model *model)
{
    int i, k;
    int vertex_index, texture_index, normal_index;
    double x, y, z, normal_x, normal_y, normal_z, u, v;

    glBegin(GL_TRIANGLES);

    for (i = 0; i < model->n_triangles; ++i)
    {
        for (k = 0; k < 3; ++k)
        {
            normal_index = model->triangles[i].points[k].normal_index;
            normal_x = model->normals[normal_index].x;
            normal_y = model->normals[normal_index].y;
            normal_z = model->normals[normal_index].z;
            glNormal3d(normal_x, normal_y, normal_z);

            vertex_index = model->triangles[i].points[k].vertex_index;
            x = model->vertices[vertex_index].x;
            y = model->vertices[vertex_index].y;
            z = model->vertices[vertex_index].z;
            switch (k)
            {
            case 0:
                glTexCoord2f(0, 0);
                break;
            case 1:
                glTexCoord2f(0.1 * z, 0);
                break;
            case 2:
                glTexCoord2f(0, 0.01);
                break;
            }
            glVertex3d(x, y, z);
        }
    }

    glEnd();
}

void draw_quads(const struct Model *model)
{
    int i, k;
    int vertex_index, texture_index, normal_index;
    double x, y, z, u, v;

    glBegin(GL_QUADS);

    for (i = 0; i < model->n_quads; ++i)
    {
        for (k = 0; k < 4; ++k)
        {

            texture_index = model->quads[i].points[k].texture_index;
            u = model->texture_vertices[texture_index].u;
            v = model->texture_vertices[texture_index].v;
            // NOTE: The 1-v is model file specific!
            glTexCoord2f(u, 1 - v);

            vertex_index = model->quads[i].points[k].vertex_index;
            x = model->vertices[vertex_index].x;
            y = model->vertices[vertex_index].y;
            z = model->vertices[vertex_index].z;
            glVertex3d(x, y, z);
        }
    }

    glEnd();
}

void draw_normals(const struct Model *model, double length)
{
    int i;
    double x1, y1, z1, x2, y2, z2;

    glColor3f(0, 0, 1);

    glBegin(GL_LINES);

    for (i = 0; i < model->n_vertices; ++i)
    {
        x1 = model->vertices[i].x;
        y1 = model->vertices[i].y;
        z1 = model->vertices[i].z;
        x2 = x1 + model->normals[i].x * length;
        y2 = y1 + model->normals[i].y * length;
        z2 = z1 + model->normals[i].z * length;
        glVertex3d(x1, y1, z1);
        glVertex3d(x2, y2, z2);
    }
    glEnd();
}

void draw_room_left(Room room)
{
    glBindTexture(GL_TEXTURE_2D, room.left);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-room_size, 0, -room_size);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-room_size, room_size, -room_size);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-room_size, room_size, room_size);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-room_size, 0, room_size);
    glEnd();
}
void draw_room_right(Room room)
{
    glBindTexture(GL_TEXTURE_2D, room.right);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(room_size, 0, room_size);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(room_size, room_size, room_size);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(room_size, room_size, -room_size);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(room_size, 0, -room_size);
    glEnd();
}
void draw_room_front(Room room)
{
    glBindTexture(GL_TEXTURE_2D, room.front);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-room_size, 0, -room_size);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(room_size, 0, -room_size);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(room_size, room_size, -room_size);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-room_size, room_size, -room_size);
    glEnd();
}
void draw_room_back(Room room)
{
    glBindTexture(GL_TEXTURE_2D, room.back);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-room_size, 0, room_size);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-room_size, room_size, room_size);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(room_size, room_size, room_size);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(room_size, 0, room_size);
    glEnd();
}
void draw_room_top(Room room)
{
    glBindTexture(GL_TEXTURE_2D, room.top);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(room_size, room_size, room_size);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(room_size, room_size, -room_size);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-room_size, room_size, -room_size);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-room_size, room_size, room_size);

    glEnd();
}

void draw_room_bottom(Room room)
{
    glBindTexture(GL_TEXTURE_2D, room.bottom);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(room_size, 0, room_size);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(room_size, 0, -room_size);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-room_size, 0, -room_size);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-room_size, 0, room_size);

    glEnd();
}

void draw_environment(World world)
{
    glEnable(GL_TEXTURE_2D);
    displayList1 = glGenLists(1);
    glNewList(displayList1, GL_COMPILE);
    GLfloat material_specular[] = {1, 1, 1, 1};
    GLfloat material_ambient[] = {0.9, 0.9, 0.9, 1};
    GLfloat material_diffuse[] = {1, 1, 1, 1};
    GLfloat material_shininess[] = {100.0};

    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);

    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glScalef(20.0f, 20.0f, 20.0f);

    glEndList();

    boxList = glGenLists(1);
    glNewList(boxList, GL_COMPILE);

    GLfloat zeros[] = {0, 0, 0};
    GLfloat ones[] = {1, 1, 1};

    glMaterialfv(GL_FRONT, GL_DIFFUSE, zeros);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ones);

    draw_room_left(world.room);
    draw_room_right(world.room);
    draw_room_front(world.room);
    draw_room_back(world.room);
    draw_room_top(world.room);
    draw_room_bottom(world.room);

    glEndList();

    glDisable(GL_TEXTURE_2D);
}

void draw_teapot_for_light()
{
    glPushMatrix();
    glTranslatef(190, 10, 0);
    glScalef(10, 10, 10);
    glutSolidTeapot(1.0);
    glPopMatrix();
}

void draw_entities(World world)
{
    glEnable(GL_TEXTURE_2D);
    draw_teapot_for_light();
    glCallList(boxList);

    glDisable(GL_TEXTURE_2D);
}
