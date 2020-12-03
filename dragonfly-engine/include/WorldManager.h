#pragma once
#include "Manager.h"
#include "Object.h"
#include "ObjectList.h"

#define MAX_ALTITUDE 5

namespace df {

	// Two - letter access macro
	#define WM WorldManager::getInstance()

	class WorldManager : public Manager {

	private:
		WorldManager();							// Private (a singleton)
		WorldManager(WorldManager const&);		// Don’t allow copy
		void operator=(WorldManager const&);	// Don’t allow assignment

		ObjectList m_updates;	// All Objects in world to update
		ObjectList m_deletions;	// All Objects in world to delete
		int m_id_count = 0;		// Incremented whenever an object is made, ensuring they have unique ID numbers
		Box m_boundary;			// Outer limit of the world dimensions
		Box m_view;				// Player view of the game world
		Object* p_view_following; // Object view is following

	public:
		~WorldManager();

		// Get the one and only instance of the WorldManager .
		static WorldManager &getInstance();

		// Start up game world (initialize everything to empty)
		// Return 0
		int startUp();

		// Shutdown game world (delete all game world Objects)
		void shutDown();

		// Set/Get game world boundary
		void setBoundary(Box new_boundary);
		Box getBoundary() const;

		// Set player view of game world
		void setView(Box new_view);
		Box getView() const;

		// Set view to center window on position view pos
		// View edge will not go beyond world boundary
		void setViewPosition(Vector view_pos);
		
		// Set view to center window on Object
		// Set to NULL to stop following
		// If p_new_view_following not legit, return −1 else return 0
		int setViewFollowing(Object* p_new_view_following);
		Object* getViewFollowing() const;

		// Insert Object into world. Return 0 if ok, else −1
		int insertObject(Object* p_o);

		// Remove Object from world. Return 0 if ok, else −1
		int removeObject(Object* p_o);

		// Delete all game objects
		void deleteAllObjects();

		// Delete object of type
		void deleteObjectsOfType(std::string obj_type);
		
		// Return list of all Objects in world
		ObjectList getAllObjects() const;
		
		// Return list of all Objects in world matching type
		ObjectList objectsOfType(std::string type) const;

		// Return a pointer to the object of the given id, if it exists
		Object* objectOfId(int id) const;

		// Return list of Objects collided with at position ‘where’
		// Collisions only with solid Objects
		// Does not consider if p_o is solid or not
		ObjectList getCollisions(const Object* p_o, Vector where) const;
		
		// Move Object
		// If collision with solid, send collision events
		// If no collision with solid, move ok else don't move Object
		// If Object is Spectral, move ok
		// Return 0 if move ok, else −1 if collision with solid
		int moveObject(Object * p_o, Vector where);

		// Update world
		// Delete Objects marked for deletion
		void update();

		// Draw all objects
		void draw();
		
		// Indicate Object is to be deleted at end of current game loop
		// Return 0 if ok, else −1
		int markForDelete(Object* p_o);

		// Return a unique ID number for an object
		int getNewId();

		// Broadcast an event to every object in the world
		int broadcastEvent(const Event* p_e);
	};
}