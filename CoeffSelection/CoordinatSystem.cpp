#pragma once
#include "CoordinatSystem.h"


void CoordinatSys::setPixRect(Rect _pixRect)
{
    pixRect = _pixRect;
}

const Rect& CoordinatSys::getPixRect()
{
    return pixRect;
}


void CoordinatSys::setNullCoor(Vector _pixRect)
{
    nullCoor = _pixRect;
}


const Vector& CoordinatSys::getNullCoor()
{
    return nullCoor;
}


void CoordinatSys::setNullPointUnit(Vector _nullPointUnit)
{
    nullPointUnit = _nullPointUnit;
}

const Vector& CoordinatSys::getNullPointUnit()
{
    return nullPointUnit;
}




CoordinatSys::CoordinatSys(HDC outputDc /* = txDC()*/)
{
    intepretK_.x = 1;
    intepretK_.y = 1;

}

/*
Vector CoordinatSys::drawCircle (Ball ball)
{
    //Vector intepretK = {}; //= scalePix / coorSize;

    //intepretK.x = scalePix.x / coorSize.x;
    //intepretK.y = scalePix.y / coorSize.y;

    Vector pixPos = interpret (ball.pos);

    double rScale = (intepretK_.x + intepretK_.y) / 2;

    //$s
    txSetFillColor (ball.color);

    //if (pixPos.x > sysBorderPix_.left () && pixPos.y > sysBorderPix_.top () && pixPos.x < sysBorderPix_.right () && pixPos.y < sysBorderPix_.bottom ())
    if (pixPos.x < (startPosPix_.x + scalePix_.x) && pixPos.x > startPosPix_.x)
    {
        if (pixPos.y < (startPosPix_.y + scalePix_.y) && pixPos.y > startPosPix_.y)
        {
            txCircle (pixPos.x, pixPos.y, ball.r * rScale);
        }
    }
    //_getch ();

    return pixPos;

}
*/



void CoordinatSys::drawLine(Vector startLPos, Vector finishLPos, COLORREF color)
{
    Vector startLPixPos = interpret(startLPos);

    Vector finishLPixPos = interpret(finishLPos);

    $s

        txSetFillColor(color);

    txLine(startLPos.x, startLPos.y, finishLPos.x, finishLPos.y);

}

/*
Vector CoordinatSys::drawFunc (const char *func)
{
    int l = strlen (func);
    double y = 0;
    int temp = 0;

    for (int x = 0; x < (finishPosPix_ - nullCoor_).x; x++)
    {

        for (int i = 0; i < l; i++)
        {
            if (func[i] == 'x')
            {
                if (func[i + 1] == '^')
                {
                    sscanf ((char *)func[i + 2], "%lf", temp);
                    y += pow (x, temp);
                }
                if (func[i + 1] == '*')
                {
                    sscanf ((char *)func[i + 2], "%lf", temp);
                }
            }
        }
    }
}
*/


Vector CoordinatSys::drawCircle(const Vector& vector, double r/* = 1*/)
{
    //Vector intepretK = {}; //= scalePix / coorSize;

    //intepretK.x = scalePix.x / coorSize.x;
    //intepretK.y = scalePix.y / coorSize.y;

    Vector pixPos = interpret(vector);

    double rScale = 1;//(intepretK_.x + intepretK_.y) / 2;

    //if (pixPos.x > sysBorderPix_.left() && pixPos.y > sysBorderPix_.top() && pixPos.x < sysBorderPix_.right() && pixPos.y < sysBorderPix_.bottom())
    if (pixPos < finishPosPix_)
    {
        if (pixPos > startPosPix_)
        {
            txCircle(pixPos.x, pixPos.y, r * rScale);
        }
    }

    return pixPos;

}

void CoordinatSys::clean()
{
    drawAxis();
}

/*
void CoordinatSys::drawAxis(Vector nDelta)
{
    lastNDelta = nDelta;
    txSetFillColor(RGB(240, 240, 240));
    txRectangle(startPosPix_.x, startPosPix_.y, finishPosPix_.x, finishPosPix_.y);

    txSetColor(RGB(120, 120, 120), 3);
    txSetFillColor(RGB(120, 120, 120));
    txLine(nullCoor_.x, finishPosPix_.y, nullCoor_.x, startPosPix_.y);
    drawArrows({ nullCoor_.x - nullCoor_.x, startPosPix_.y - finishPosPix_.y }, { nullCoor_.x, startPosPix_.y });

    txLine(startPosPix_.x, nullCoor_.y, finishPosPix_.x, nullCoor_.y);
    drawArrows({ finishPosPix_.x - startPosPix_.x, -nullCoor_.y + nullCoor_.y }, { finishPosPix_.x, nullCoor_.y });
    txSetColor(RGB(200, 200, 200), 1);



    Vector roundDelta = { (humanRound(((((finishPosPix_.x) - (startPosPix_.x))) / (nDelta.x)))),
                         (humanRound(((((finishPosPix_.y) - (startPosPix_.y))) / (nDelta.y))))
    };

    char text[20] = {};


    txSelectFont("Arial", config.font);

    Vector num = nullPoint;
    for (int x = 0; x < nDelta.x * 10; x++)
    {
        if (nullCoor_.x + ((num.x - nullPoint.x) * intepretK_.x) < finishPosPix_.x && startPosPix_.x < nullCoor_.x + ((num.x - nullPoint.x) * intepretK_.x))
        {
            sprintf(text, "%lg", num.x);
            txLine(nullCoor_.x + ((num.x - nullPoint.x) * intepretK_.x), finishPosPix_.y, nullCoor_.x + ((num.x - nullPoint.x) * intepretK_.x), startPosPix_.y);
            txTextOut(nullCoor_.x + ((num.x - nullPoint.x) * intepretK_.x), nullCoor_.y, text);
        }
        if (nullCoor_.x - ((num.x - nullPoint.x) * intepretK_.x) < finishPosPix_.x && startPosPix_.x < nullCoor_.x - ((num.x - nullPoint.x) * intepretK_.x))
        {
            sprintf(text, "%lg", -num.x);
            txLine(nullCoor_.x - ((num.x - nullPoint.x) * intepretK_.x), finishPosPix_.y, nullCoor_.x - ((num.x - nullPoint.x) * intepretK_.x), startPosPix_.y);
            txTextOut(nullCoor_.x - ((num.x - nullPoint.x) * intepretK_.x), nullCoor_.y, text);
        }

        num.x += roundDelta.x;
    }

    //txTextOut (nullCoor_.x + ((num.x - roundDelta.x) * intepretK_.x), nullCoor_.y, text);

    for (int y = 0; y < nDelta.y * 10; y++)
    {

        if (nullCoor_.y + ((num.y - nullPoint.y) * intepretK_.y) < finishPosPix_.y && startPosPix_.y < nullCoor_.y + ((num.y - nullPoint.y) * intepretK_.y))
        {
            sprintf(text, "%lg", num.y);
            txTextOut(nullCoor_.x, nullCoor_.y + ((num.y - nullPoint.y) * intepretK_.y), text);
            txLine(startPosPix_.x, nullCoor_.y + ((num.y - nullPoint.y) * intepretK_.y), finishPosPix_.x, nullCoor_.y + ((num.y - nullPoint.y) * intepretK_.y));
        }

        if (nullCoor_.y - ((num.y - nullPoint.y) * intepretK_.y) < finishPosPix_.y && startPosPix_.y < nullCoor_.y - ((num.y - nullPoint.y) * intepretK_.y))
        {
            sprintf(text, "%lg", num.y);
            txTextOut(nullCoor_.x, nullCoor_.y - ((num.y - nullPoint.y) * intepretK_.y), text);
            txLine(startPosPix_.x, nullCoor_.y - ((num.y - nullPoint.y) * intepretK_.y), finishPosPix_.x, nullCoor_.y - ((num.y - nullPoint.y) * intepretK_.y));
        }

        num.y += roundDelta.y;
    }

    if (!config.xName.empty())
    {
        txSetTextAlign(TA_RIGHT);
        txSetColor(TX_BLACK);
        txSetFillColor(TX_BLACK);
        txTextOut(finishPosPix_.x - 5, nullCoor_.y + 5, xName);
    }

    if (!config.yName.empty())
    {
        txSetTextAlign(TA_RIGHT);
        txSetColor(TX_BLACK);
        txSetFillColor(TX_BLACK);
        txTextOut(nullCoor_.x - 5, startPosPix_.y, yName);
    }

}
*/


void txSetAllColors(COLORREF color, HDC dc = txDC())
{
    txSetColor(color, dc);
    txSetFillColor(color, dc)
}


void CoordinatSys::drawAxis()
{
    txSetAllColors(config.backgroundColor, dc);
    txRectangle(r);
    
}


void CoordinatSys::drawAxisLines()
{
    pixRect.sort();
    txLine(pixRect.pos.x, nullCoor.y, pixRect.finishPos.x, nullCoor.y, dc);
}

void drawArrows(const Vector& mainVector, const Vector& finishPoint)
{
    Vector perpendicular1 = makePerpendikularLine(mainVector);
    Vector perpendicular2 = perpendicular1 * -1;

    Vector arrow1 = perpendicular1 * 0.01 - mainVector * 0.02;
    Vector arrow2 = perpendicular2 * 0.01 - mainVector * 0.02;

    Vector arrow1finishPoint = ((arrow1)+finishPoint);
    Vector arrow2finishPoint = ((arrow2)+finishPoint);

    txLine(finishPoint.x, finishPoint.y, arrow1finishPoint.x, arrow1finishPoint.y);
    txLine(finishPoint.x, finishPoint.y, arrow2finishPoint.x, arrow2finishPoint.y);
}

Vector makePerpendikularLine(const Vector& mainVector)
{
    Vector perpendikularLine = {};
    perpendikularLine.x = mainVector.y;
    perpendikularLine.y = -(mainVector.x);

    return perpendikularLine;
}


double humanRound(double delta)
{
    /*
    * 0.1 -> 0.1
    * 0.12 -> 0.1
    * 0.2  -> .
    * 0.23 -> 0.25
    * 0.25 -> 0.25
    * 0.28 -> 0.25
    * 0.3  -> 0.25
    * 0.35 - >0.5
    * 0.4  0.5
    * 0.5  0.5
    * 0.6  0.5
    * 0.7  1
    * 0.8  1
    * 0.9  1
    * 3.14 exp:1
    *
    */

    //printf ("\n::%d::\n", delta);
    delta = fabs(delta);
    double exp = log10(delta);
    double mantissa = delta / (pow(10, ceil(exp)));

    //double mantissa = frexp (delta, &order);

    //printf ("Delta: %lf\tExp: %lf \tMantissa: %lf\n", delta, exp, mantissa);

    if (mantissa < 0.15) mantissa = 0.1;
    if (0.15 <= mantissa && mantissa < 0.23) mantissa = 0.2;
    if (0.23 <= mantissa && mantissa < 0.35) mantissa = 0.25;
    if (0.35 <= mantissa && mantissa < 0.65) mantissa = 0.5;
    if (0.65 <= mantissa && mantissa <= 1)   mantissa = 1;

    //printf ("delta: %lf, fDelta: %lf\n", delta, mantissa * pow (10, ceil(exp)));


    return mantissa * pow(10, ceil(exp));
}


Vector CoordinatSys::interpret(Vector vector)
{
    return nullCoor_ + (intepretK_ * (vector - nullPoint));
}

Vector CoordinatSys::convertFromPixels(Vector vector)
{
    Vector answer = {};
    answer = ((vector - nullCoor_) / intepretK_) + nullPoint;
    return answer;
}




Vector CoordinatSys::getXBound()
{
    Vector minAnswer = convertFromPixels(startPosPix_);
    Vector maxAnswer = convertFromPixels(finishPosPix_);

    Vector answer = {};
    answer.x = std::min(minAnswer.x, maxAnswer.x);
    answer.y = std::max(minAnswer.x, maxAnswer.x);
    return answer;
}


Vector CoordinatSys::getYBound()
{
    Vector minAnswer = convertFromPixels(startPosPix_);
    Vector maxAnswer = convertFromPixels(finishPosPix_);

    Vector answer = {};
    answer.x = std::min(minAnswer.y, maxAnswer.y);
    answer.y = std::max(minAnswer.y, maxAnswer.y);
    return answer;
}

