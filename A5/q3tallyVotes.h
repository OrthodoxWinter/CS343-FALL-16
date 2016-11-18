#ifndef __TALLY_VOTES_H__
#define __TALLY_VOTES_H__

#include "AutomaticSignal.h"
_Monitor Printer;

#if defined( IMPLTYPE_EXT )            // external scheduling monitor solution
// includes for this kind of vote-tallier
_Monitor TallyVotes {
    // private declarations for this kind of vote-tallier
#elif defined( IMPLTYPE_INT )          // internal scheduling monitor solution
// includes for this kind of vote-tallier
_Monitor TallyVotes {
    // private declarations for this kind of vote-tallier
    uCondition voteQueue;
#elif defined( IMPLTYPE_INTB )         // internal scheduling monitor solution with barging
// includes for this kind of vote-tallier
_Monitor TallyVotes {
    // private declarations for this kind of vote-tallier
    uCondition bench;                  // only one condition variable (you may change the variable name)
    unsigned int serving, numVoters;
    void wait();                       // barging version of wait
    void signalAll();                  // unblock all waiting tasks
#elif defined( IMPLTYPE_AUTO )         // automatic-signal monitor solution
// includes for this kind of vote-tallier
_Monitor TallyVotes {
    // private declarations for this kind of vote-tallier
    bool groupFormed;
    AUTOMATIC_SIGNAL
#elif defined( IMPLTYPE_TASK )         // internal/external scheduling task solution
_Task TallyVotes {
    uCondition serverQueue, voterQueue;
    bool terminate;
    void main();
    // private declarations for this kind of vote-tallier
#else
    #error unsupported voter type
#endif
    const unsigned int groupSize;
    Printer &printer;
    unsigned int count;
    int pictureTour;
    // common declarations
  public:                              // common interface
    TallyVotes( unsigned int group, Printer &printer );
    enum Tour { Picture, Statue };
    Tour vote( unsigned int id, Tour ballot );
#ifdef IMPLTYPE_EXT
    ~TallyVotes();
#endif
  private:
    Tour result;
#ifdef IMPLTYPE_EXT
    unsigned int voteId;
    Tour voteBallot;
#endif
};

#endif