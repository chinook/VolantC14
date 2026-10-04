#ifndef UI_SPLASHPRESENTER_HPP
#define UI_SPLASHPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class UI_splashView;

class UI_splashPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    UI_splashPresenter(UI_splashView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~UI_splashPresenter() {}

private:
    UI_splashPresenter();

    UI_splashView& view;
};

#endif // UI_SPLASHPRESENTER_HPP
