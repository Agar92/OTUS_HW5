/*!
 * \file view.h
 * Implementation of the MVC View component
*/
#pragma once

#include <observer.h>

//!  MVC View component class 
/*!
 *  \details MVC View class
 */
class VectorRedactor_View : public Observer {
public:
	/*! \brief Constructor of the MVC View component @see VectorRedactor_View class defintion*/
    /*! \details Sets the MVC Model component object member field of the class @see VectorRedactor_View*/
    /*! \param[in] _model a pointer to an MVC Model object*/
	VectorRedactor_View(VectorRedactor_Model * _model){
		model = std::unique_ptr<VectorRedactor_Model>(_model);
		model->addObserver(this);
	}
	//! Update View
	/*! \details Update GUI on the signal from the user or the model */
	void update() override
    {
    	RenderGUI();
   	}
   	//! Render GUI
	/*! Rerender the application GUI. Here should be some realization
	 * of the GUI rendering function by the means of the GUI library used in the project.
	 */
   	void RenderGUI(){}
   	~VectorRedactor_View(){
   		model.release();
   	}
private:
	std::unique_ptr<VectorRedactor_Model> model;
};