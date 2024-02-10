#include "../main.hpp"

//  void P5::arc(float x, float y, float w, float h, float start, float stop, ArcMode mode = ArcMode::CHORD){
//     if(!this->_isParametersValid("arc", {})){
//         return;
//     }
//     if(start == stop){
//         return;
//     }

//     start = this._toRadians(start);
//     stop = this._toRadians(stop);

//     // negative width and height are allowed
//     w = Math.abs(w);
//     h = Math.abs(h);


//     const vals = canvas.modeAdjust(x, y, w, h, this._renderer._ellipseMode);
//     const angles = this._normalizeArcAngles(start, stop, vals.w, vals.h, true);

//  }