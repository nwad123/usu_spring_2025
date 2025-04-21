datatype Matrix =
  | Upper(seq<Matrix>)
  | Bottom(seq<real>)

class Mat {
  const RANK : nat
  const DIMS : array<nat>
  var underlying : seq<real>

  ghost predicate isValid()
    reads this.DIMS
  {
    && RANK == DIMS.Length
    && forall dim :: dim in DIMS[..] ==> dim > 0
  }

  constructor(rank: nat, dims: seq<nat>, underlying: seq<real>)
    requires rank == |dims|
    requires forall i :: 0 <= i < |dims| ==> dims[i] > 0
    requires num_elements(dims) <= |underlying|
    ensures isValid()
  {
    RANK := rank;
    DIMS := new [rank](i requires 0 <= i < rank => dims[i]);
  }
}

method x()
{
  var x := new Mat(0, [], []);
  var y := new Mat(1, [2], [1.0, 2.0]);
  var z := new Mat(1, [3], [1.0, 2.0, 3.0]);
  var a := new Mat(1, [1,1], [1.0]);
  var b := new Mat(1, [3], [1.0, 2.0, 3.0]);
  var c := new Mat(1, [3], [1.0, 2.0, 3.0]);
}