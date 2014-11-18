/**
 * Virtual function pointer table for the 'abstract' class State.
 * These functions must be implemented by classes inheriting from
 * State.
 *@param start should run initialization routines.
 *@param standBy should do nothing but wait.
 *@param detumble should correct spatial orientation.
 *@param doScience should collect science data.
 */
struct State_vtable
{
  void (* start)(struct Satellite *);
  void (* standBy)(struct Satellite *);
  void (* detumble)(struct Satellite *);
  void (* doScience)(struct Satellite *);
};

/**
 * Class State
 * This class provides an abstract interface for classes to inherit from.
 * The functions implemented by the child class determine what is done
 * by the functions in that State. For example, if a PowerSave class
 * inherited from State then the PowerSave's doScience and detumble
 * method would probably do nothing because the state would be trying
 * to save power.
 */
struct State
{
  struct State_vtable *vtable;
};


