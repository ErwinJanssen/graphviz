/* $Id$ $Revision$ */
/* vim:set shiftwidth=4 ts=8: */

/**********************************************************
*      This software is part of the graphviz package      *
*                http://www.graphviz.org/                 *
*                                                         *
*            Copyright (c) 1994-2004 AT&T Corp.           *
*                and is licensed under the                *
*            Common Public License, Version 1.0           *
*                      by AT&T Corp.                      *
*                                                         *
*        Information and Software Systems Research        *
*              AT&T Research, Florham Park NJ             *
**********************************************************/

#include "selection.h"
#include "viewport.h"
int rectintersects(float x,float y,float W,float H)
{
	//returns 1 if rect is completely in the clip rect
	//0 if they intersect
	//-1 if completely out

	int s[4];
	s[0]=( ((x >=view->Selection.X)&& (x <= (view->Selection.X + view->Selection.W) ))) ? 1:0;
	s[1]=( (((x+W) >=view->Selection.X)&& ((x+W) <= (view->Selection.X + view->Selection.W) ))) ? 1:0;

	s[2]=( ((y >=view->Selection.Y)&& (y <= (view->Selection.Y + view->Selection.H) ))) ? 1:0;
	s[3]=( (((y+H) >=view->Selection.Y)&& ((y+H) <= (view->Selection.Y + view->Selection.H) ))) ? 1:0;

	
	if (s[0] && s[1] && s[2] && s[3])
		return 1;
	if (s[0] || s[1] || s[2] || s[3])
		return 0;
	return -1;

}
int lineintersects(float X1,float X2,float Y1,float Y2)
{
	//line segment
	//X1,Y1 point 1
	//X2,Y3 point 2
	//rectangle
	//RX,RY lower left corner of rectangle
	//RW width of rectangle
	//RH height of ractangle
	//returns 1 if line segment is completely in the rect
	//0 if they intersect
	//-1 if completely out
	float x,y,m,iter;
	float RX,RY,RW,RH;
	int intersects,in;
	RX=view->Selection.X;
	RY=view->Selection.Y;
	RW=view->Selection.W;
	RH=view->Selection.H;
	if((is_point_in_rectangle(X1,Y1,RX,RY,RW,RH)) && (is_point_in_rectangle(X2,Y2,RX,RY,RW,RH)))
		return 1;
	if((is_point_in_rectangle(X1,Y1,RX,RY,RW,RH)) || (is_point_in_rectangle(X2,Y2,RX,RY,RW,RH)))
		return 0;
	//to be absolute or not to be one
	if(X1 > X2)
	{
		x=X2;
		y=Y2;
		X2=X1;
		Y2=Y1;
		X1=x;
		Y1=y;
	}
	x=X1;
	//iter
	iter=RW/(float)SELECTION_SEGMENT_DIVIDER;
	m=(Y2-Y1)/(X2-X1);

	in=1;
	intersects=0;
	while (x <= X2)
	{
		x=x+iter;
		y=Y1+m*(x-X1);		
		if ( !is_point_in_rectangle(x,y,RX,RY,RW,RH))
			in=0;
		else
			intersects=1;

	}
	if (in==1)
		return 1;
	if (intersects==1)
		return 0;
	return -1;
}
int is_point_in_rectangle(float X,float Y,float RX,float RY,float RW,float RH)
{
	if ((X >= RX) && (X <= (RX+RW) ) && (Y >= RY) && (Y <= (RY+RH)))
		return 1;
	else
		return 0;


}

int SelectBeziers(xdot_op* op)
{
	if(!view->Selection.Active)
		return 0;
	switch (view->Selection.Type)
	{
	case 0:
		if (view->Selection.AlreadySelected)
			return 0;
		if( spline_x_rect(op))
		{
			if ( ((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected==0)
			{
				((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected=1;
				select_object (view->g[view->activeGraph],((xdot*)(op->parentxdot))->obj);
				view->Selection.AlreadySelected=1;
			}
			else
			{
				((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected=0;
				deselect_object (view->g[view->activeGraph],((xdot*)(op->parentxdot))->obj);
				view->Selection.AlreadySelected=1;
			}
		}
			break;
	case 1:
//		if ( ((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected==1)
//			return 0;
		if(  ( ((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->selectionflag  != -1 )  &&       (spline_in_rect(op)) )
		{
			((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Preselected=1;
//      		  select_object (view->g[view->activeGraph],((xdot*)(op->parentxdot))->obj);
			  view->Selection.AlreadySelected=1;
		}
		else
		{
			((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Preselected=0;
//      		  deselect_object (view->g[view->activeGraph],((xdot*)(op->parentxdot))->obj);
			  view->Selection.AlreadySelected=1;
			((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->selectionflag = -1;			
		}
		break;
	case 2:
		if ( ((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected==1)
			return 0;
		if(spline_x_rect(op))
		{
			((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected=1;
      		  select_object (view->g[view->activeGraph],((xdot*)(op->parentxdot))->obj);
			  view->Selection.AlreadySelected=1;
		}
		break;
	default:
		return 0;
	}
	return 1;

}

int SelectPolygon(xdot_op* op)
{

	if(!view->Selection.Active)
		return 0;
	switch (view->Selection.Type)
	{
	case 0:
		if (view->Selection.AlreadySelected)
			return 0;

		
			if ((point_within_polygon( op)) ||     (polygon_x_rect(op)))
			{
				  
				if ( ((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected==0)
				{
					((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected=1;
					  select_object (view->g[view->activeGraph],((xdot*)(op->parentxdot))->obj);
					  view->Selection.AlreadySelected=1;

				}
				else
				{
					((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected=0;
					  deselect_object (view->g[view->activeGraph],((xdot*)(op->parentxdot))->obj);
					  view->Selection.AlreadySelected=1;

				}
			}
			break;
	case 1:
		if ( ((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected==1)
			return 0;
		if(  ( ((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->selectionflag  != -1 )  &&       (polygon_in_rect(op)) )
		{
			((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Preselected=1;
//      		  select_object (view->g[view->activeGraph],((xdot*)(op->parentxdot))->obj);
//			  view->Selection.AlreadySelected=1;

		}
		else
		{
			((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Preselected=0;
//			deselect_object (view->g[view->activeGraph],((xdot*)(op->parentxdot))->obj);
			view->Selection.AlreadySelected=1;
			((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->selectionflag = -1;			
		}
	

		break;
	case 2:
		if ( ((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected==1)
			return 0;
		if(polygon_x_rect(op))
		{
			((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected=1;
      		  select_object (view->g[view->activeGraph],((xdot*)(op->parentxdot))->obj);
			  view->Selection.AlreadySelected=1;

		}
		break;
	default:
		return 0;
	}
	return 1;
}

int SelectPolyline(xdot_op* op)
{
	if(!view->Selection.Active)
		return 0;
	switch (view->Selection.Type)
	{
	case 0:
		if (view->Selection.AlreadySelected)
			return 0;

		
			if ( polyline_x_rect(op)   )
			{
				  
				if ( ((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected==0)
				{
					((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected=1;
					  select_object (view->g[view->activeGraph],((xdot*)(op->parentxdot))->obj);
					  view->Selection.AlreadySelected=1;

				}
				else
				{
					((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected=0;
					  deselect_object (view->g[view->activeGraph],((xdot*)(op->parentxdot))->obj);
					  view->Selection.AlreadySelected=1;

				}
			}
			break;
	case 1:
		if ( ((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected==1)
			return 0;
		if(  ( ((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->selectionflag  != -1 )  &&       (polyline_in_rect(op)) )
		{
			((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Preselected=1;

		}
		else
		{
			((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Preselected=0;
			view->Selection.AlreadySelected=1;
			((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->selectionflag = -1;			
		}
	

		break;
	case 2:
		if ( ((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected==1)
			return 0;
		if(polyline_x_rect(op))
		{
			((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected=1;
      		  select_object (view->g[view->activeGraph],((xdot*)(op->parentxdot))->obj);
			  view->Selection.AlreadySelected=1;

		}
		break;
	default:
		return 0;
	}

	return 1;

}
int SelectEllipse(xdot_op* op)
{
	if(!view->Selection.Active)
		return 0;
	switch (view->Selection.Type)
	{
	case 0:
		if (view->Selection.AlreadySelected)
			return 0;

			if( point_within_ellipse(op))		
			{
				if ( ((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected==0)
				{
					((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected=1;
					  select_object (view->g[view->activeGraph],((xdot*)(op->parentxdot))->obj);
					  view->Selection.AlreadySelected=1;

				}
				else
				{
					((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected=0;
					  deselect_object (view->g[view->activeGraph],((xdot*)(op->parentxdot))->obj);
					  view->Selection.AlreadySelected=1;

				}
			}
			else if( ellipse_x_rect(op))
			{
				  
				if ( ((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected==0)
				{
					((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected=1;
					  select_object (view->g[view->activeGraph],((xdot*)(op->parentxdot))->obj);
					  view->Selection.AlreadySelected=1;

				}
				else
				{
					((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected=0;
					  deselect_object (view->g[view->activeGraph],((xdot*)(op->parentxdot))->obj);
					  view->Selection.AlreadySelected=1;

				}
			}
			break;
	case 1:
		if ( ((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected==1)
			return 0;
		if(  ( ((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->selectionflag  != -1 )  &&  (ellipse_in_rect(op)) )
		{
			((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Preselected=1;
			  view->Selection.AlreadySelected=1;

		}
		else
		{
			((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Preselected=0;
			view->Selection.AlreadySelected=1;
			((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->selectionflag = -1;			
		}

		break;
	case 2:
		if ( ((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected==1)
			return 0;
		if(ellipse_x_rect(op))
		{
			((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected=1;
      		  select_object (view->g[view->activeGraph],((xdot*)(op->parentxdot))->obj);
			  view->Selection.AlreadySelected=1;

		}
		break;
	default:
		return 0;
	}
	return 1;
}


int SelectText(xdot_op* op)
{
	if(!view->Selection.Active)
		return 0;
	switch (view->Selection.Type)
	{
	case 0:
		if (view->Selection.AlreadySelected)
			return 0;
			if( text_x_rect(op))
			{
				  
				if ( ((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected==0)
					((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected=1;
				else
					((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected=0;
			}
			break;
	case 1:
		if ( ((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected==1)
			return 0;
		if(text_in_rect(op))
		{
			((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected=1;
      		  select_object (view->g[view->activeGraph],((xdot*)(op->parentxdot))->obj);
			  view->Selection.AlreadySelected=1;

		}
		break;
	case 2:
		if ( ((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected==1)
			return 0;
		if(text_x_rect(op))
		{
			((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected=1;
      		  select_object (view->g[view->activeGraph],((xdot*)(op->parentxdot))->obj);
			  view->Selection.AlreadySelected=1;
		}
		break;
	default:
		return 0;
	}
	return 1;

}

int SelectImage(xdot_op* op)
{
	if(!view->Selection.Active)
		return 0;
	switch (view->Selection.Type)
	{
	case 0:
		if (view->Selection.AlreadySelected)
			return 0;
			if( image_x_rect(op))
			{
				  
				if ( ((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected==0)
				{
					((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected=1;
	      		  select_object (view->g[view->activeGraph],((xdot*)(op->parentxdot))->obj);
					view->Selection.AlreadySelected=1;
				}
				else
					((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected=0;
			}
			break;
	case 1:
		if ( ((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected==1)
			return 0;
		if(image_in_rect(op))
			((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected=1;
		break;
	case 2:
		if ( ((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected==1)
			return 0;
		if(image_x_rect(op))
			((custom_object_data*)AGDATA(((xdot*)(op->parentxdot))->obj))->Selected=1;
		break;
	default:
		return 0;
	}
	return 1;

}




int spline_in_rect(xdot_op* op)
{
	//JUST SEND ALL CONTROL POINTS IN 3D ARRAYS
	float tempX[4];
	float tempY[4];
	float tempZ[4];
	int temp=0;
	int i=0;
	for (i=0;i < op->u.bezier.cnt ; i= i + 1)
	{
		if (temp==4)
		{
			if(!within_bezier(tempX,tempY,tempZ,0))
				return 0;
			tempX[0]=(float)op->u.bezier.pts[i-1].x;
			tempY[0]=(float)op->u.bezier.pts[i-1].y;
			tempZ[0]=(float)op->u.bezier.pts[i-1].z;
			temp=1;
			tempX[temp]=(float)op->u.bezier.pts[i].x;			
			tempY[temp]=(float)op->u.bezier.pts[i].y;			
			tempZ[temp]=(float)op->u.bezier.pts[i].z;			
			temp=temp+1;
		}
		else
		{
			tempX[temp]=(float)op->u.bezier.pts[i].x;
			tempY[temp]=(float)op->u.bezier.pts[i].y;
			tempZ[temp]=(float)op->u.bezier.pts[i].z;
			temp=temp+1;
		}
	}
	if(!within_bezier(tempX,tempY,tempZ,0))
			return 0;
	else
			return 1;
}
int spline_x_rect(xdot_op* op)
{
	//JUST SEND ALL CONTROL POINTS IN 3D ARRAYS
	float tempX[4];
	float tempY[4];
	float tempZ[4];
	int temp=0;
	int i=0;
	for (i=0;i < op->u.bezier.cnt ; i= i + 1)
	{
		if (temp==4)
		{
			if(within_bezier(tempX,tempY,tempZ,1))
				return 1;
			tempX[0]=(float)op->u.bezier.pts[i-1].x;
			tempY[0]=(float)op->u.bezier.pts[i-1].y;
			tempZ[0]=(float)op->u.bezier.pts[i-1].z;
			temp=1;
			tempX[temp]=(float)op->u.bezier.pts[i].x;			
			tempY[temp]=(float)op->u.bezier.pts[i].y;			
			tempZ[temp]=(float)op->u.bezier.pts[i].z;			
			temp=temp+1;
		}
		else
		{
			tempX[temp]=(float)op->u.bezier.pts[i].x;
			tempY[temp]=(float)op->u.bezier.pts[i].y;
			tempZ[temp]=(float)op->u.bezier.pts[i].z;
			temp=temp+1;
		}
	}
	if(within_bezier(tempX,tempY,tempZ,1))
			return 1;
	else
			return 0;
}
int polygon_in_rect(xdot_op* op)
{
	int ind=0;
	for (ind=0;ind < op->u.polygon.cnt-1;ind ++)
	{
		if( lineintersects((float)op->u.polygon.pts[ind].x,(float)op->u.polygon.pts[ind+1].x,(float)op->u.polygon.pts[ind].y,(float)op->u.polygon.pts[ind+1].y)!=1)
			return 0;
	};
	return 1;
}
int polygon_x_rect(xdot_op* op)
{
	int ind=0;
	for (ind=0;ind < op->u.polygon.cnt-1;ind ++)
	{
		if( lineintersects((float)op->u.polygon.pts[ind].x,(float)op->u.polygon.pts[ind+1].x,(float)op->u.polygon.pts[ind].y,(float)op->u.polygon.pts[ind+1].y)>=0)
			return 1;
	};
	return 0;
}
int polyline_in_rect(xdot_op* op)
{
	int ind=0;
	for (ind=0;ind < op->u.polygon.cnt-1;ind ++)
	{
		if( lineintersects((float)op->u.polygon.pts[ind].x,(float)op->u.polygon.pts[ind+1].x,(float)op->u.polygon.pts[ind].y,(float)op->u.polygon.pts[ind+1].y)!=1)
			return 0;
	};
	return 1;
}
int polyline_x_rect(xdot_op* op)
{
	int ind=0;
	for (ind=0;ind < op->u.polygon.cnt-1;ind ++)
	{
		if( lineintersects((float)op->u.polygon.pts[ind].x,(float)op->u.polygon.pts[ind+1].x,(float)op->u.polygon.pts[ind].y,(float)op->u.polygon.pts[ind+1].y)>=1)
			return 1;
	};
	return 0;
}
int text_in_rect(xdot_op* op)
{
	if( rectintersects((float)op->u.text.x,(float)op->u.text.y,(float)op->u.text.x+op->u.text.width,(float)op->u.text.y+(float)op->u.text.size)==1 )
		return 1;
	return 0;

}
int text_x_rect(xdot_op* op)
{
	if( rectintersects((float)op->u.text.x,(float)op->u.text.y,(float)op->u.text.x+op->u.text.width,(float)op->u.text.y+(float)op->u.text.size)>=1 )
		return 1;
	return 0;

}
int image_in_rect(xdot_op* op)
{
	if( rectintersects((float)op->u.image.pos.x  ,(float)op->u.image.pos.y,(float)op->u.image.pos.w,(float)op->u.image.pos.h)==1)
		return 1;
	return 0;
}
int image_x_rect(xdot_op* op)
{
	if( rectintersects((float)op->u.image.pos.x  ,(float)op->u.image.pos.y,(float)op->u.image.pos.w,(float)op->u.image.pos.h)>=0)
		return 1;
	return 0;
}

int within_bezier(GLfloat* xp,GLfloat* yp,GLfloat* zp,int isx)
{
	double Ax = xp[0]; double Ay = yp[0]; double Az = zp[0];
	double Bx = xp[1]; double By = yp[1]; double Bz = zp[1];
	double Cx = xp[2]; double Cy = yp[2]; double Cz = zp[2];
	double Dx = xp[3]; double Dy = yp[3]; double Dz = zp[3];
	double X;
	double Y;
	double Z;
	double Xprev;
	double Yprev;
	double Zprev;
	int i = 0;//loop index
	// Variable
	double a = 1.0;
	double b = 1.0 - a;
	int in=1;
	int inter=0;
	for(i = 0; i <= 20; i++)
	{
	  // Get a point on the curve
		X = Ax*a*a*a + Bx*3*a*a*b + Cx*3*a*b*b + Dx*b*b*b;
		Y = Ay*a*a*a + By*3*a*a*b + Cy*3*a*b*b + Dy*b*b*b;
		Z = Az*a*a*a + Bz*3*a*a*b + Cz*3*a*b*b + Dz*b*b*b;
		if (i>0)
		{
			if(lineintersects((float)Xprev,(float)X,(float)Yprev,(float)Y) >=0)	//intersection
			{
				if(isx)
					return 1;
			}
			if(!(lineintersects((float)Xprev,(float)X,(float)Yprev,(float)Y)==1))	//withing the rect
			{
				if(!isx)
					return 0;
			}
		}
		Xprev=X;
		Yprev=Y;
		Zprev=Z;

		a -= 0.05;
		b = 1.0 - a;
	}
	if(isx)
		return 0;
	else
		return 1;

}


int ellipse_x_rect(xdot_op* op)
{
	float x,y,xradius,yradius;

	double Xprev;
	double Yprev;
	double Zprev;

	int i=0;
	x=(float)op->u.ellipse.x;
	y=(float)op->u.ellipse.y;
	xradius=(float)op->u.ellipse.w;
	yradius=(float)op->u.ellipse.h;
	for (i=0; i < 360; i=i+1)
	{
      //convert degrees into radians
		float degInRad = i*(float)DEG2RAD;
		if (i>0)
		{
			if(lineintersects((float)Xprev,x+(float)cos(degInRad)*xradius,(float)Yprev,y+(float)sin(degInRad)*yradius) >=0)	//intersection
					return 1;
		}

		Xprev=x+cos(degInRad)*xradius;
		Yprev=y+sin(degInRad)*yradius;
		Zprev=0;
   }
   return 0;
}

int ellipse_in_rect(xdot_op* op)
{
	float x,y,xradius,yradius;

	double Xprev;
	double Yprev;
	double Zprev;

	int i=0;
	x=(float)op->u.ellipse.x;
	y=(float)op->u.ellipse.y;
	xradius=(float)op->u.ellipse.w;
	yradius=(float)op->u.ellipse.h;
	for (i=0; i < 360; i=i+1)
	{
      //convert degrees into radians
		float degInRad = (float)i*(float)DEG2RAD;
		if (i>0)
		{
			if(!(lineintersects((float)Xprev,(float)x+(float)cos(degInRad)*xradius,(float)Yprev,y+(float)sin(degInRad)*yradius)==1))	//withing the rect
					return 0;
		}

		Xprev=x+cos(degInRad)*xradius;
		Yprev=y+sin(degInRad)*yradius;
		Zprev=0;
   }
   return 1;
}

int point_within_ellipse( xdot_op* op)
{

	float dx,dy,ex,ey,ea,eb,px,py ;
	float a;
	
	ex=(float)op->u.ellipse.x;
	ey=(float)op->u.ellipse.y;
	ea=(float)op->u.ellipse.w;
	eb=(float)op->u.ellipse.h;
	px=view->Selection.X+(float)SINGLE_SELECTION_WIDTH/(float)2;
	py=view->Selection.Y+(float)SINGLE_SELECTION_WIDTH/(float)2;
	dx = px - ex;
	dy = py - ey;
	a=(dx*dx)/(ea*ea) + (dy*dy)/(eb*eb);
	return (a <= 1);
}
 
int point_within_polygon(xdot_op* op)
//int pnpoly(int npol, float *xp, float *yp, float x, float y)
{
	int i, j, c = 0;
	int npol=op->u.polygon.cnt;
	float x,y;
	op->u.polygon.pts[i].y;
	op->u.polygon.pts[i].x;
	x=view->Selection.X+SINGLE_SELECTION_WIDTH/2;
	y=view->Selection.Y+SINGLE_SELECTION_WIDTH/2;

	for (i = 0, j = npol-1; i < npol; j = i++) {
		
		
		if ((((op->u.polygon.pts[i].y <= y) && (y < op->u.polygon.pts[j].y)) ||
		((op->u.polygon.pts[j].y <= y) && (y < op->u.polygon.pts[i].y))) &&
			(x < (op->u.polygon.pts[j].x - op->u.polygon.pts[i].x) * (y - op->u.polygon.pts[i].y) / (op->u.polygon.pts[j].y - op->u.polygon.pts[i].y) + op->u.polygon.pts[i].x))
		c = !c;
	}
	return c;
}


//select functions
int select_node(Agraph_t* g,Agnode_t* N)
{
	int ind=0;
	//check if in the list
	for (ind=0;ind < ((custom_graph_data*)AGDATA(g))->selectedNodesCount ; ind ++ )
	{	
		if(  ((custom_graph_data*)AGDATA(g))->selectedNodes[ind] == N)
			return 0;
	}
	//for single selections i think realloc is ok, for mass selections i ll figure out something else
	((custom_graph_data*)AGDATA(g))->selectedNodes=realloc(((custom_graph_data*)AGDATA(g))->selectedNodes,sizeof(Agnode_t*)*(((custom_graph_data*)AGDATA(g))->selectedNodesCount+1));
	((custom_graph_data*)AGDATA(g))->selectedNodes[((custom_graph_data*)AGDATA(g))->selectedNodesCount]=N;
	((custom_graph_data*)AGDATA(g))->selectedNodesCount++;
	((custom_object_data*)AGDATA(N))->Selected=1;
	return 1;
}
int select_edge(Agraph_t* g,Agedge_t* E)
{
	int ind=0;
	//check if in the list
	for (ind=0;ind < ((custom_graph_data*)AGDATA(g))->selectedEdgesCount ; ind ++ )
	{	
		if(((custom_graph_data*)AGDATA(g))->selectedEdges[ind] == E)
			return 0;
	}
	//for single selections i think realloc is ok, for mass selections i ll figure out something else
	((custom_graph_data*)AGDATA(g))->selectedEdges=realloc(((custom_graph_data*)AGDATA(g))->selectedEdges,sizeof(Agnode_t*)*(((custom_graph_data*)AGDATA(g))->selectedEdgesCount+1));
	((custom_graph_data*)AGDATA(g))->selectedEdges[((custom_graph_data*)AGDATA(g))->selectedEdgesCount]=E;
	((custom_graph_data*)AGDATA(g))->selectedEdgesCount++;
	((custom_object_data*)AGDATA(E))->Selected=1;
	return 1;

}
int select_object (Agraph_t* g,void* obj)
{
	switch(AGTYPE(obj))
	{
	case AGNODE:
		select_node(g,obj); 
		break;
	case AGEDGE:
		select_edge(g,obj); 
		break;
	case AGRAPH:
		select_graph(g,obj); 
		break;
	default:
		break;
	}
	return 1;
}
int deselect_object (Agraph_t* g,void* obj)
{
	switch(AGTYPE(obj))
	{
	case AGNODE:
		deselect_node(g,obj); 
		break;
	case AGEDGE:
		deselect_edge(g,obj); 
		break;
	case AGRAPH:
		deselect_graph(g,obj); 
		break;
	default:
		break;
	}
	return 1;
}

//select functions
int select_graph(Agraph_t* g,Agraph_t* G)
{
	int ind=0;
	//check if in the list
	for (ind=0;ind < ((custom_graph_data*)AGDATA(g))->selectedGraphsCount ; ind ++ )
	{	
		if(((custom_graph_data*)AGDATA(g))->selectedGraphs[ind] == G)
			return 0;
	}
	//for single selections i think realloc is ok, for mass selections i ll figure out something else
	((custom_graph_data*)AGDATA(g))->selectedGraphs=realloc(((custom_graph_data*)AGDATA(g))->selectedGraphs,sizeof(Agnode_t*)*(((custom_graph_data*)AGDATA(g))->selectedGraphsCount+1));
	((custom_graph_data*)AGDATA(g))->selectedGraphs[((custom_graph_data*)AGDATA(g))->selectedGraphsCount]=G;
	((custom_graph_data*)AGDATA(g))->selectedGraphsCount++;
	((custom_object_data*)AGDATA(G))->Selected=1;
	return 1;
}
int deselect_node(Agraph_t* g,Agnode_t* N)
{
	int ind=0;
	int valid=0;
	//check if in the list
	for (ind=0;ind < ((custom_graph_data*)AGDATA(g))->selectedNodesCount ; ind ++ )
	{	
		if(valid)
			((custom_graph_data*)AGDATA(g))->selectedNodes[ind-1]=((custom_graph_data*)AGDATA(g))->selectedNodes[ind];
		if( ((custom_graph_data*)AGDATA(g))->selectedNodes[ind] == N)
			valid=1;
	}
	//for single selections i think realloc is ok, for mass selections i ll figure out something else
	if(valid)
	{
		((custom_graph_data*)AGDATA(g))->selectedNodes=realloc(((custom_graph_data*)AGDATA(g))->selectedNodes,sizeof(Agnode_t*)*(((custom_graph_data*)AGDATA(g))->selectedNodesCount-1));
		((custom_graph_data*)AGDATA(g))->selectedNodesCount--;
		((custom_object_data*)AGDATA(N))->Selected=0;
		((custom_object_data*)AGDATA(N))->selectionflag=0;
	}
	return 1;	

}
int deselect_edge(Agraph_t* g,Agedge_t* E)
{
	int ind=0;
	int valid=0;
	//check if in the list
	for (ind=0;ind < ((custom_graph_data*)AGDATA(g))->selectedEdgesCount ; ind ++ )
	{	
		if(valid)
			((custom_graph_data*)AGDATA(g))->selectedEdges[ind-1]=((custom_graph_data*)AGDATA(g))->selectedEdges[ind];
		if( ((custom_graph_data*)AGDATA(g))->selectedEdges[ind] == E)
			valid=1;
	}
	//for single selections i think realloc is ok, for mass selections i ll figure out something else
	if(valid)
	{
		((custom_graph_data*)AGDATA(g))->selectedEdges=realloc(((custom_graph_data*)AGDATA(g))->selectedEdges,sizeof(Agnode_t*)*(((custom_graph_data*)AGDATA(g))->selectedEdgesCount-1));
		((custom_graph_data*)AGDATA(g))->selectedEdgesCount--;
		((custom_object_data*)AGDATA(E))->Selected=0;
		((custom_object_data*)AGDATA(E))->selectionflag=0;

	}
	return 1;
}
int deselect_graph(Agraph_t* g,Agraph_t* G)
{
	int ind=0;
	int valid=0;
	//check if in the list
	for (ind=0;ind < ((custom_graph_data*)AGDATA(g))->selectedGraphsCount ; ind ++ )
	{	
		if(valid)
			((custom_graph_data*)AGDATA(g))->selectedGraphs[ind-1]=((custom_graph_data*)AGDATA(g))->selectedGraphs[ind];
		if( ((custom_graph_data*)AGDATA(g))->selectedGraphs[ind] == G)
			valid=1;
	}
	//for single selections i think realloc is ok, for mass selections i ll figure out something else
	if(valid)
	{
		((custom_graph_data*)AGDATA(g))->selectedGraphs=realloc(((custom_graph_data*)AGDATA(g))->selectedGraphs,sizeof(Agnode_t*)*(((custom_graph_data*)AGDATA(g))->selectedGraphsCount-1));
		((custom_graph_data*)AGDATA(g))->selectedGraphsCount--;
		((custom_object_data*)AGDATA(G))->Selected=0;
		((custom_object_data*)AGDATA(G))->selectionflag=0;

	}
	return 1;
}

int select_all_nodes(Agraph_t* g)
{
	Agnode_t *n;
	for (n = agfstnode(g); n; n = agnxtnode(g, n))
	{
			select_node(g,n);
	}
	return 1;	

}
int select_all_edges(Agraph_t* g)
{
   Agnode_t *n;
	Agedge_t *e;

	
	n = agfstnode(g);
	
	for (n = agfstnode(g); n; n = agnxtnode(g, n))
	{
		for (e = agfstout(g,n) ; e ; e = agnxtout (g,e))
		{
			select_edge(g,e);
		}
	}
	return 1;	

}
int select_all_graphs(Agraph_t* g)
{
	Agraph_t *s;
	for (s = agfstsubg(g); s; s = agnxtsubg(s))
		select_graph(g,s);
	return 1;	
}

int deselect_all_nodes(Agraph_t* g)
{
   Agnode_t *n;

	
	n = agfstnode(g);
	

	for (n = agfstnode(g); n; n = agnxtnode(g, n))
	{
			deselect_node(g,n);
	}
	return 1;	


}
int deselect_all_edges(Agraph_t* g)
{
{
   Agnode_t *n;
	Agedge_t *e;
	n = agfstnode(g);
	for (n = agfstnode(g); n; n = agnxtnode(g, n))
	{
		for (e = agfstout(g,n) ; e ; e = agnxtout (g,e))
		{
			deselect_edge(g,e);
		}
	}
	return 1;	
}


}
int deselect_all_graphs(Agraph_t* g)
{
	Agraph_t *s;
	for (s = agfstsubg(g); s; s = agnxtsubg(s))
		deselect_graph(g,s);
	return 1;
}
int select_all(Agraph_t* g)
{
	select_all_nodes(g);
	select_all_edges(g);
	select_all_graphs(g);
	return 1;

}
int deselect_all(Agraph_t* g)
{
	deselect_all_nodes(g);
	deselect_all_edges(g);
	deselect_all_graphs(g);
	return 1;
}
int line_intersects (float* x,float* y,float* X,float* Y)
{
	//x,y are arrayf of float for two lines parameters theyt hold 4 points with x and y
	//limitx and limity are float arrays with two points, thse points are the end points of the second line
	//X,Y are the variables to put intersection point coordinates in
	pointf pA,pB,pC,pD,pX;
	pA.x=x[0];pA.y=y[0];
	pB.x=x[1];pB.y=y[1];
	pC.x=x[2];pC.y=y[2];
	pD.x=x[3];pD.y=y[3];

	if(intersect (pA, pB, pC, pD, &pX))
	{
		*X=(float)pX.x;
		*Y=(float)pX.y;
		if ( (pX.x >=x[2]-0.01)	&&	(pX.x <x[3]+0.01) &&
			(pX.y >=y[2]-0.01)	&&	(pX.x <y[3]+0.01))
		{
			return 1;

		}
		return 0;

	}
	else
		return 0;

}

int point_within_ellips_with_coords(float ex,float ey,float ea,float eb,float px,float py)
{

	float dx,dy;
	float a;
	dx = px - ex;
	dy = py - ey;
	a=(dx*dx)/(ea*ea) + (dy*dy)/(eb*eb);
	return (a <= 1);
}


