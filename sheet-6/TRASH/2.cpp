#include <stdio.h>
#include <string.h>
#include <net/if.h>
#include <sys/ioctl.h>

unsigned char cMacAddr[8]; // Server's MAC address

static int GetSvrMacAddress( char *pIface )
{
	int nSD; // Socket descriptor
	struct ifreq sIfReq; // Interface request
	struct if_nameindex *pIfList; // Ptr to interface name index
	struct if_nameindex *pListSave; // Ptr to interface name index

//
// Initialize this function
//
	pIfList = (struct if_nameindex *)NULL;
	pListSave = (struct if_nameindex *)NULL;

//
// Create a socket that we can use for all of our ioctls
//
	nSD = socket( PF_INET, SOCK_STREAM, 0 );
	if ( nSD < 0 )
	{
	// Socket creation failed, this is a fatal error
	printf( "File %s: line %d: Socket failed\n", __FILE__, __LINE__ );
	return( 0 );
	}

	pIfList = pListSave = if_nameindex();

	for ( pIfList; *(char *)pIfList != 0; pIfList++ )
	{
		//
		// Determine if we are processing the interface that we
		// are interested in
		//
		if ( strcmp(pIfList->if_name, pIface) )
		// Nope, check the next one in the list
		continue;
		strncpy( sIfReq.ifr_name, pIfList->if_name, IF_NAMESIZE );

		//
		// Get the MAC address for this interface
		//
		if ( ioctl(nSD, SIOCGIFHWADDR, &sIfReq) != 0 )
		{
			// We failed to get the MAC address for the interface
			printf( "File %s: line %d: Ioctl failed\n", __FILE__, __LINE__ );
			return( 0 );
		}
		memmove( (void *)&cMacAddr[0], (void *)&sIfReq.ifr_ifru.ifru_hwaddr.sa_data[0], 6 );
		break;
		}

	//
	// Clean up things and return
	//
	if_freenameindex( pListSave );
	//close( nSD );
	return( 1 );
}

int main( int argc, char * argv[] )
{
	//
	// Initialize this program
	//
	bzero( (void *)&cMacAddr[0], sizeof(cMacAddr) );
	if ( !GetSvrMacAddress("eth0") )
	{
		// We failed to get the local host's MAC address
		printf( "Fatal error: Failed to get local host's MAC address\n" );
		}
		printf( "HWaddr %02X:%02X:%02X:%02X:%02X:%02X\n",
		cMacAddr[0], cMacAddr[1], cMacAddr[2],
		cMacAddr[3], cMacAddr[4], cMacAddr[5] );

	//
	// And exit
	//

}
