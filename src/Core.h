#pragma once

// Current Configuration
#define DEBUG_MODE

// Debug Mode specific settings
#ifdef DEBUG_MODE
#define LOG_LEVEL DEBUG_LEVEL
#endif

// Release Mode specific settings
#ifdef RELEASE_MODE
// disable logs
#define LOG_LEVEL NO_LOG
#endif
