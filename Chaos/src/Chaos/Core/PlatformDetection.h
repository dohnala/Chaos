// Platform detection using predefined macros
#ifdef _WIN32
	#ifdef _WIN64
		/* Windows x64  */
		#define CH_PLATFORM_WINDOWS
	#else
		/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
#endif