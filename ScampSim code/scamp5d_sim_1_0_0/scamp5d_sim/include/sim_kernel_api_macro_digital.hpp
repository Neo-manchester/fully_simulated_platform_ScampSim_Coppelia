/*!

\file

\ingroup VS_SCAMP5

\author Jianing Chen

*/

#ifndef SCAMP5_KERNEL_API_MACRO_DIGITAL_HPP
#define SCAMP5_KERNEL_API_MACRO_DIGITAL_HPP


#include "sim_kernel_api.hpp"


namespace scamp5_kernel_api{


    using namespace SCAMP5_PE;

    /*!
    * @brief 	logic operation Rl := NOT Rl
    *
    */
    void NOT( DREG Rl );

    /*!
    * @brief 	logic operation Rl := Rl OR Rx
    *
    */
    void OR( DREG Rl, DSRC Rx );

    /*!
    * @brief 	logic operation Rl := Rl NOR Rx
    *
    */
    void NOR( DREG Rl, DSRC Rx );

	/*!
	 * @brief 	digital neighbour OR, Ra := Rx_dir1 OR Rx_dir2 ...; (also modify R1 R2 R3 R4).
	 *
	 */
    void DNEWS( DREG y, DSRC x0, const int dir, const bool boundary = 0 );

	/*!
	* @brief 	async-propagation on R12, masked by R0, boundaries are considered as '0'
	*
	*/
	void PROP0();

	/*!
	* @brief 	async-propagation on R12, masked by R0, boundaries are considered as '1'
	*
	*/
	void PROP1();

    /*!
    * @brief 	Rl := Rx AND Ry
    *
    */
    void AND( DREG Rl, DSRC Rx, DSRC Ry );

    /*!
    * @brief 	Rl := Rx NAND Ry
    *
    */
    void NAND( DREG Rl, DSRC Rx, DSRC Ry );

	/*!
	* @brief 	Ra := Rb AND Rx, Rb = !Rx
	*
	*/
	void ANDX(DREG Ra, DREG Rb, DSRC Rx);

	/*!
	* @brief 	Ra := Rb NAND Rx, Rb = !Rx
	*
	*/
	void NANDX(DREG Ra, DREG Rb, DSRC Rx);

    /*!
    * @brief 	Rl := Rx IMP Ry
    *
    */
    void IMP( DREG Rl, DSRC Rx, DSRC Ry );

    /*!
    * @brief 	Rl := Rx NIMP Ry
    *
    */
    void NIMP( DREG Rl, DSRC Rx, DSRC Ry );

    /*!
    * @brief 	Rl := Rx XOR Ry, Rl !@ Ry
    *
    */
    void XOR( DREG Rl, DREG Rx, DSRC Ry );

    /*!
    * @brief 	Rl := Ry IF Rx = 1, Rl := Rz IF Rx = 0.
    */
    void MUX( DREG Rl, DSRC Rx, DSRC Ry, DSRC Rz );

    /*!
    * @brief 	Rl := 0 IF Rx = 1, Rl := Rl IF Rx = 0.
    */
    void CLR_IF( DREG Rl, DSRC Rx );

    void REFRESH( DREG y );

	void PROP0();

	void PROP1();

};

#endif
