/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef BRIDGE_H
#define BRIDGE_H

class Bridge : public Test
{
public:

	enum
	{
		e_count = 30
	};

	Bridge()
	{
		b2Body* ground = null;
		{
			b2BodyDef bd;
			ground = this->m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.Set(b2Vec2(-40.0, 0.0), b2Vec2(40.0, 0.0));
			ground->CreateFixture(&shape, 0.0);
		}

		{
			b2PolygonShape shape;
			shape.SetAsBox(0.5, 0.125f);

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 20.0;
			fd.friction = 0.2;

			b2RevoluteJointDef jd;

			b2Body* prevBody = ground;
			for (int32 i = 0; i < e_count; ++i)
			{
				b2BodyDef bd;
				bd.type = b2Body::b2_dynamicBody;
				bd.position.Set(-14.5 + 1.0 * i, 5.0);
				b2Body* body = this->m_world->CreateBody(&bd);
				body->CreateFixture(&fd);

				b2Vec2 anchor(-15.0 + 1.0 * i, 5.0);
				jd.Initialize(prevBody, body, anchor);
				this->m_world->CreateJoint(&jd);

				if (i == (e_count >> 1))
				{
					this->m_middle = body;
				}
				prevBody = body;
			}

			b2Vec2 anchor(-15.0 + 1.0 * e_count, 5.0);
			jd.Initialize(prevBody, ground, anchor);
			this->m_world->CreateJoint(&jd);
		}

		for (int32 i = 0; i < 2; ++i)
		{
			b2Vec2 vertices[3];
			vertices[0].Set(-0.5, 0.0);
			vertices[1].Set(0.5, 0.0);
			vertices[2].Set(0.0, 1.5);

			b2PolygonShape shape;
			shape.Set(vertices, 3);

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 1.0;

			b2BodyDef bd;
			bd.type = b2Body::b2_dynamicBody;
			bd.position.Set(-8.0 + 8.0 * i, 12.0);
			b2Body* body = this->m_world->CreateBody(&bd);
			body->CreateFixture(&fd);
		}

		for (int32 i = 0; i < 3; ++i)
		{
			b2CircleShape shape;
			shape.m_radius = 0.5;

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 1.0;

			b2BodyDef bd;
			bd.type = b2Body::b2_dynamicBody;
			bd.position.Set(-6.0 + 6.0 * i, 10.0);
			b2Body* body = this->m_world->CreateBody(&bd);
			body->CreateFixture(&fd);
		}
	}

	static Test* Create()
	{
		return new Bridge;
	}

	b2Body* m_middle;
};

#endif
