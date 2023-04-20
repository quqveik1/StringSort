#pragma once

int cCmps = 0;
int cExchanges = 0;

int& getCCmps()
{
    return cCmps;
}

void setCCmps(int _amountOfCmps)
{
    cCmps = _amountOfCmps;
}

int& getCExchanges()
{
    return cExchanges;
}

void setCExchanges(int exchanges)
{
    cExchanges = exchanges;
}

