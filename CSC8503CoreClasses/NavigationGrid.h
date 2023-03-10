#pragma once
#include "NavigationMap.h"
#include <string>
namespace NCL {
	namespace CSC8503 {
		struct GridNode {
			GridNode* parent;

			GridNode* connected[4];
			int		  costs[4];

			Vector3		position;

			float f;
			float g;

			int type;

			GridNode() {
				for (int i = 0; i < 4; ++i) {
					connected[i] = nullptr;
					costs[i] = 0;
				}
				f = 0;
				g = 0;
				type = 0;
				parent = nullptr;
			}
			~GridNode() {	}
		};

		class NavigationGrid : public NavigationMap	{
		public:
			NavigationGrid();
			NavigationGrid(const std::string&filename);
			~NavigationGrid();
			GridNode* GetAllNodes() {
				return allNodes;
			}
			int GetGridWidth() {
				return gridWidth;
			}
			int getGridHeight() {
				return gridHeight;
			}
			bool FindPath(const Vector3& from, const Vector3& to, NavigationPath& outPath) override;
			bool FindOffsetPath(const Vector3& from, const Vector3& to, NavigationPath& outPath, Vector3 offset) {
				Vector3 f = Vector3(from.x - offset.x, from.y - offset.y, from.z - offset.z);
				Vector3 t = Vector3(to.x - offset.x, to.y - offset.y, to.z - offset.z);
				return FindPath(f, t, outPath);
			};
				
		protected:
			bool		NodeInList(GridNode* n, std::vector<GridNode*>& list) const;
			GridNode*	RemoveBestNode(std::vector<GridNode*>& list) const;
			float		Heuristic(GridNode* hNode, GridNode* endNode) const;
			int nodeSize;
			int gridWidth;
			int gridHeight;

			GridNode* allNodes;
		};
	}
}

