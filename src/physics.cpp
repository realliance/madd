#include "physics.h"

Physics::Physics():collisionConfig{new btDefaultCollisionConfiguration},
                   dispatcher{new btCollisionDispatcher(collisionConfig)},
                   overlappingPairCache{new btDbvtBroadphase()},
                   solver{new btSequentialImpulseConstraintSolver},
                   dynamicsWorld{new btDiscreteDynamicsWorld(dispatcher,
                                                             overlappingPairCache,
                                                             solver,
                                                             collisionConfig)}{
    dynamicsWorld->setGravity(btVector3(0,-10,0));
}

Physics::~Physics(){
    	//remove the rigidbodies from the dynamics world and delete them
	for (int i = dynamicsWorld->getNumCollisionObjects(); i > 0; i--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		dynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}

	//delete collision shapes
	for (int j = 0; j < collisionShapes.size(); j++)
	{
		btCollisionShape* shape = collisionShapes[j];
		collisionShapes[j] = 0;
		delete shape;
	}


    delete dynamicsWorld;
    delete solver;
    delete overlappingPairCache;
    delete dispatcher;
    delete collisionConfig;
}

void Physics::Tick(){
    dynamicsWorld->stepSimulation(1.f/60.f,10);

}