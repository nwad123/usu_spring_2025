# Max Element Hoare Proof

let $$ P(i) = i \le N \vee \forall j : j \le i \implies a[j] \le max $$

test 

\begin{align*}
\text{1-3: } & \{ true \} i \coloneq 0, max \coloneq 0 \{ P(i) \} \\
\text{4-9: } & \{P(i) \vee i < N \} \text{ loop } \{ P(i) \} \\
\text{10:  } & \{P(i) \vee \neg (i < N)\} \{\forall (0 \le j < N) : a[j] \le max\} \\
\end{align*}
