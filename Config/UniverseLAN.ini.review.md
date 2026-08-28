# Review: `Config/UniverseLAN.ini`

## Finding — every installation ships the same authentication key

- **Severity:** High
- **Evidence:** The default `[Authentication]` key at line 27 is a committed, reusable base64 value, while the file states that clients and servers use it to accept/refuse connections.
- **Impact:** Anyone who obtains the public configuration can authenticate to any server left on this default, including the default `0.0.0.0` listener, and can impersonate an authorized client. This key is authentication material even though it is not an encryption key.
- **Suggested fix:** Generate a unique key during installation/first run, reject the known default (or require an explicit operator-supplied key), and provide a safe way to distribute the same per-server key to clients.
