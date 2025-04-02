method max(a: seq<nat>) returns (max: nat)
  ensures forall j :: 0 <= j < |a| ==> a[j] <= max
{
  var i := 0;
  var N := |a|;

  max := 0;

  while (i < N)
    invariant && i <= N
              && forall j :: 0 <= j < i ==> a[j] <= max
  {
    if (a[i] > max) {
      max := a[i];
    }
    i := i + 1;
  }
}