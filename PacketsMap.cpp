/**
 * @file PacketsMap.h
 * @brief Defines constants for packet types used in the game.
 *
 * These constants are used to identify the type of data being sent or received
 * between the server and client during gameplay.
 */

/// Packet type indicating the start of the game.
#define PACKET_TYPE_START 1

/// Packet type indicating that the game is over.
#define PACKET_TYPE_GAMEOVER 2

/// Packet type indicating the game has finished.
#define PACKET_TYPE_FINISHGAME 3

/// Packet type indicating a client has disconnected.
#define PACKET_TYPE_DISCONNECT 4