#include "particles.h"

void update_particle(int type, int i)
{
	v2i pp = inverse_index2D(i, 160);
	int aboveGround = (pp.y < 120 - 1);

	int this, up, up_right, right, down_right, down, down_left, left, up_left;
	this	= i;
	down	= this + 160;
	up		= this - 160;
	right	= this + 1;
	left	= this - 1;
	up_right	= up + 1;
	up_left		= up - 1;
	down_right	= down + 1;
	down_left	= down - 1;

	switch (type) {
		case 0: // Air
			break;

		case 1: // Sand
			if (particles[down].type == 0 && aboveGround)
			{
				particleBuffer[this].type = 0;
				particleBuffer[down].type = 1;
				return;
			}
			if (particles[down_left].type == 0 && aboveGround)
			{
				particleBuffer[this].type = 0;
				particleBuffer[down_left].type = 1;
				return;
			}
			if (particles[down_right].type == 0 && aboveGround)
			{
				particleBuffer[this].type = 0;
				particleBuffer[down_right].type = 1;
				return;
			}
			break;

		case 2: // Water
			if (particles[down].type == 0 && aboveGround)
			{
				particleBuffer[i].type = 0;
				particleBuffer[i + 160].type = 2;
				return;
			}
			if (particles[down_left].type == 0 && aboveGround)
			{
				particleBuffer[i].type = 0;
				particleBuffer[i + 160 - 1].type = 2;
				return;
			}
			if (particles[down_right].type == 0 && aboveGround)
			{
				particleBuffer[i].type = 0;
				particleBuffer[i + 160 + 1].type = 2;
				return;
			}

			// Flow right or left
			if (rand() % 2)
			{
				if (particles[i - 1].type == 0)
				{
					particleBuffer[i].type = 0;
					particleBuffer[i - 1].type = 2;
					return;
				}
			}
			else
			{
				if (particles[i + 1].type == 0)
				{
					particleBuffer[i].type = 0;
					particleBuffer[i + 1].type = 2;
					return;
				}
			}
			break;
	}
}

void update_particles(int moveParticles)
{
	for (int i = 0; i < ENTITY_COUNT; i++)
	{
		entity particle = particles[i];

		if (moveParticles)
			update_particle(particle.type, i);
	}
}

void draw_particles()
{
	for (int i = 0; i < ENTITY_COUNT; i++)
	{
		entity particle = particleBuffer[i];

		v2i pp = inverse_index2D(i, 160);
		SDL_Rect rect = { pp.x * 4, pp.y * 4, 4, 4 };

		//wColor color = particle_types[particle.type].color;
		SDL_SetRenderDrawColor(state.simulation->renderer_handle, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(state.simulation->renderer_handle, &rect);

		particles[i] = particle;
	}
}

void add_particle(v2i point, int drawParticle)
{
	point.x = point.x > 160 ? 160 : point.x;
	point.x = point.x < 0 ? 0 : point.x;
	point.y = point.y > 120 ? 120 : point.y;
	point.y = point.y < 0 ? 0 : point.y;
	particleBuffer[index2D(point.x, point.y, 160)].type = drawParticle;
}
