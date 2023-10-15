/*!
 * \file observer.h
 * Implementation of the pattern "Observer"
*/
#pragma once

#include <vector>

/*! \brief Abstract class "Observer" */
class Observer
{
public:
    //! A pure virtual member funtion
    /*! Pure virtual member function.
     *  It is used for updating the view (Observer)
     *  as soon as the changes are made in model (Observable)
     */
    virtual void update() = 0;
    /*! Virtual destructor */
    virtual ~Observer(){}
};

/*! \brief Interface for the class "Observable" */
class Observable
{
public:
   //! Add an "Observer" to an "Observable" object @see Observer
   /*!
    *  \param[in] observer   a pointer to an "Observer" object
    *  \return void
    */
   void addObserver(Observer *observer)
   {
      observers.push_back( std::unique_ptr<Observer>(observer) );
   }
   //! Notify all the "Observer" objects of an update in the "Observable" object @see Observer
   /*! \details
    *  \return void
    */
   void notifyUpdate()
   {
      for(size_t i = 0; i < observers.size(); i++) observers[i]->update();
   }
//! Virtual destructor
	virtual ~Observable(){
		for(size_t i = 0; i < observers.size(); i++) observers[i].release();
	}
private:
   std::vector<std::unique_ptr<Observer>> observers;
};