#ifndef PARTICLES_H
#define PARTICLES_H

#include "waspsim/wasp.h"

typedef struct
{
	int type;
} entity;

typedef struct
{
	wColor color;
} particle_type;

#define ENTITY_COUNT (120 * 160)
entity particles[ENTITY_COUNT];
entity particleBuffer[ENTITY_COUNT];

particle_type particle_types[3] = {
	{ {0, 0, 0, 0} },					// Air
	{ {255, 255, 0, 255} },				// Sand
	{ {100, 100, 255, 255} }			// Water
};


void update_particles(int updateParticles);
void draw_particles();
void add_particle(v2i point, int drawParticle);

#endif
