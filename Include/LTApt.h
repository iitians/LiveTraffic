/// @file       LTApt.h
/// @brief      Access to X-Plane's `apt.dat` file(s) and data
/// @author     Birger Hoppe
/// @copyright  (c) 2020 Birger Hoppe
/// @copyright  Permission is hereby granted, free of charge, to any person obtaining a
///             copy of this software and associated documentation files (the "Software"),
///             to deal in the Software without restriction, including without limitation
///             the rights to use, copy, modify, merge, publish, distribute, sublicense,
///             and/or sell copies of the Software, and to permit persons to whom the
///             Software is furnished to do so, subject to the following conditions:\n
///             The above copyright notice and this permission notice shall be included in
///             all copies or substantial portions of the Software.\n
///             THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
///             IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
///             FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
///             AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
///             LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
///             OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
///             THE SOFTWARE.

#ifndef LTApt_h
#define LTApt_h

/// Start reading apt.dat file(s), build an index
bool LTAptEnable ();

/// Update the airport data with airports around current camera position
void LTAptRefresh ();

/// @brief Return the best possible runway to auto-land at
/// @param _ac Aircraft in search for a landing spot. It's last go-to position and VSI as well as its model are of importance
/// @return Position of matching runway touch-down point, incl. timestamp and heading (of runway)
/// @note Call from separate thread, like from CalcNextPos
positionTy LTAptFindRwy (const LTAircraft& _ac);

/// Cleanup
void LTAptDisable ();

#endif /* LTApt_h */