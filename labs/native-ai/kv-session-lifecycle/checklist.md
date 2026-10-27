# KV session lifecycle — independent evidence checklist

| Question | What a passing observation would show |
| --- | --- |
| Does a request reserve a complete real K/V store? | Planned and inspected payload agree. |
| Does admission respect the raw budget? | Third 512-byte request fails at 1,024-byte budget. |
| Is lease reuse safe? | Generation changes; old lease rejected. |
| Are conversations independent? | One session's reset/release does not modify another. |
| Is rollover canonical? | Invalid shift rejected; accepted shift replaces all layers. |
| Is checkpoint comparison sufficient? | No. A live decoder identity check remains a separate requirement. |
| Have performance gains been proved? | Only if separate paired Release measurements have been run. |

The table is an educational test design, not a record of production certification.
