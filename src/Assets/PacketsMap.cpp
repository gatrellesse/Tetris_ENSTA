/**
 * @file PacketsMap.cpp
 * @brief Contains definitions for packet types and network configurations.
 */

/**
 * @brief Packet type identifier for starting the game.
 */
#define PACKET_TYPE_START 1

/**
 * @brief Packet type identifier for game over events.
 */
#define PACKET_TYPE_GAMEOVER 2

/**
 * @brief Packet type identifier for finishing the game.
 */
#define PACKET_TYPE_FINISHGAME 3

/**
 * @brief Packet type identifier for disconnect events.
 */
#define PACKET_TYPE_DISCONNECT 4

/**
 * @brief Packet type identifier for grid updates.
 */
#define PACKET_TYPE_GRID 5

/**
 * @brief Packet type identifier for score updates.
 */
#define PACKET_TYPE_SCORE 6

/**
 * @brief Localhost IP address used for testing.
 */
#define LOCAL_HOST "127.0.0.1"

/**
 * @brief IP address of the server.
 */
#define IP_SERVER "172.20.10.3"

/**
 * @brief Port number used by the server.
 */
#define PORT_SERVER 12345

/**
 * @brief Timeout duration (in seconds) for server connections.
 */
#define TIMEOUT_SERVER 30
