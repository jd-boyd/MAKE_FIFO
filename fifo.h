/**
 * @file
 * @author Joshua Boyd <jdboyd@jdboyd.net>
 * @version 1.0
 *
 * @description DESCRIPTION
 *
 * Macros for statically allocated, circular buffer, character FIFOs.
 * 
 * NOTE: change the types in MAKE_FIFO to support types other than
 *       chars.  Should just work  for any primitive type, and only
 *       a little more work for structs.
 *
 * The basic usage is to MAKE_FIFO your fifo, giving it a name and size
 * then GET, PUT, etc, the fifo of that name.
 *
 */


/**
 * Make a new FIFO.  
 *
 * @param prefix - the name of the fifo, eg. 485_tx, or 232_rx.
 * @param size - number of elements in the fifo.
 */
#define MAKE_FIFO(prefix, size)			\
char prefix ##_buffer[size+1];\
long prefix ##_next_in  = 0;\
long prefix ##_next_out = 0;\
long prefix ##_len = 0;                   \
long prefix ##_ovfl=0;

#define BUF_SIZE(prefix) (sizeof(prefix ##_buffer))

/**
 * Get and remove an element from the FIFO.
 *
 * Value here works a little like a reference in C++.  
 *
 * @param name of the fifo
 * @param Location for the returned element.
 */
#define GET(prefix, value) { \
 value=prefix ##_buffer[prefix ##_next_out]; \
 prefix ##_len--; \
prefix ##_next_out = (prefix ##_next_out+1) % BUF_SIZE(prefix);}

/**
 * Get an element from the FIFO without removing it.
 *
 * Value here works a little like a reference in C++.  
 *
 * @param name of the fifo
 * @param Location for the returned element.
 */
#define PEEK(prefix, value) { \
    value=prefix ##_buffer[prefix ##_next_out];}

/**
 * Remove an element from the FIFO without getting it.
 *
 * @param name of the fifo
 */
#define REMOVE(prefix) { \
  prefix ##_len--; \
 prefix ##_next_out = (prefix ##_next_out+1) % BUF_SIZE(prefix);}

/**
 * Return the index of the next input location.
 *
 * NOTICE: This is the only macro meant for internal use, and not the
 *         application programmer.
 */
#define NEXT_IN(prefix) ((prefix ##_next_in + 1) % BUF_SIZE( prefix ))

/**
 * Put an element into the FIFO.
 *
 * @param name of the fifo
 * @param Value of the new element.
 */
#define PUT(prefix, value) { char t; \
     prefix ##_len++; \
  prefix ##_buffer[ prefix ##_next_in ] = value; \
  t = prefix ##_next_in; \
  prefix ##_next_in = ( prefix ##_next_in + 1) % BUF_SIZE( prefix ); \
  if(prefix ##_next_in == prefix ##_next_out) {				\
     prefix ##_next_in = t; \
     prefix ##_ovfl = 1; }}

/**
 *
 * Set the points back to as if it were empty.
 * Doesn't erase the data, but only a GET or PEEK will
 * return garbage after this has been called.
 *
 * @param Name of the FIFO
 */
#define FLUSH(prefix) prefix ##_next_in  = prefix ##_next_out = 0

/**
 * Is the FIFO empty? True/False
 *
 * @param FIFO name
 * @return T/F
 */
#define IS_EMPTY(prefix) (prefix ##_next_in == prefix ##_next_out)


/**
 * Is there any data? True/False.
 * Basically the opposite of IS_EMPTY
 *
 * @param Name of the FIFO
 * @return TRUE/FALSE
 */
#define IS_NOT_EMPTY(prefix) (prefix ##_next_in != prefix ##_next_out)


/**
 * Is there any data? True/False.
 * Basically the opposite of IS_EMPTY
 * The same as IS_NOT_EMPTY
 *
 * @param Name of the FIFO
 * @return TRUE/FALSE
 */
#define KBHIT IS_NOT_EMPTY

/**
 *
 * Is the FIFO full? True/False
 *
 * @param FIFO name
 * @return TRUE/FALSE
 */
#define IS_FULL(prefix)  (prefix ##_len == BUF_SIZE(prefix)-1 )

#define DEPTH(prefix)  (prefix ##_len)
/*> prefix ##_next_out ?                                                \
                       prefix ##_next_in - prefix ##_next_out  :\
                       prefix ##_next_out - prefix ##_next_in   )
*/
#define FREE(prefix) (BUF_SIZE(prefix) - DEPTH(prefix) -1)

/**
 * Is there free space?
 * This is basically the opposite of IS_FULL
 *
 * @param FIFO name
 * @return TRUE/FALSE
 */
#define IS_NOT_FULL(prefix) (!IS_FULL(prefix))

/**
 * Is there free space?
 * THis is the same as IS_NOT_FULL.
 * This is basically the opposite of IS_FULL
 *
 * @param FIFO name
 * @return TRUE/FALSE
 */
#define AVAIL IS_NOT_FULL

#define OVFL(prefix) (prefix ##_ovfl)
