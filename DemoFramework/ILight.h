#pragma once

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Pure Abstract base class for all lights
		//
		class ILight
		{
		public:
			//
			// Enable the light.
			//
			virtual void Enable() = 0;
			//
			// Disable the light.
			//
			virtual void Disable() = 0;
		};
	}
}