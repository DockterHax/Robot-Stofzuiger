#include "MotorDriver.h"

motordriver::motordriver(PinName MLpinVooruit, PinName MLpinAchteruit, PinName MRpinVooruit, PinName MRpinAchteruit):_ML_Vooruit(MLpinVooruit), _ML_Achteruit(MLpinAchteruit), _MR_Vooruit(MRpinVooruit), _MR_Achteruit(MRpinAchteruit)
{

}
void motordriver::Vooruit(void)
{
    _ML_Vooruit = true;
    _ML_Achteruit = false;
    _MR_Vooruit = true;
    _MR_Achteruit = false;
}
void motordriver::Achteruit(void)
{
    _ML_Vooruit = false;
    _ML_Achteruit = true;
    _MR_Vooruit = false;
    _MR_Achteruit = true;
}
void motordriver::Stop(void)
{
    _ML_Vooruit = false;
    _ML_Achteruit = false;
    _MR_Vooruit = false;
    _MR_Achteruit = false;
}
void motordriver::Links(void)
{
    _ML_Vooruit = false;
    _ML_Achteruit = true;
    _MR_Vooruit = true;
    _MR_Achteruit = false;
}
void motordriver::Rechts(void)
{
    _ML_Vooruit = true;
    _ML_Achteruit = false;
    _MR_Vooruit = false;
    _MR_Achteruit = true;
}
