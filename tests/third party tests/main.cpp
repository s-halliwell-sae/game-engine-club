/*TODO
	generic property sheet with all 3rd party deps included and linked etc.
	use each 3rd party lib in at least a hello world style to confirm that they are there and working

*/

#include "lua.hpp"
#include "glm.hpp"
#include "spdlog.h"

void main()
{
	glm::vec3 a,b;

	a = a + b;

	auto console = spdlog::stdout_logger_mt("console");
	console->info("Welcome to spdlog!");
}