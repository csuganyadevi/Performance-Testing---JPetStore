# JPetStore 6 — Performance Testing Project

> **Tools:** HP LoadRunner | Dynatrace OneAgent | Apache Tomcat 9 | Java (OpenJDK 25)

A end-to-end performance testing project on the JPetStore 6 web application running on a localhost environment. The project covers workload modelling, script development, load test execution, APM monitoring, root cause analysis, and post-fix validation.

---

## Project Overview

| Item | Details |
|---|---|
| Application | JPetStore 6 (MyBatis-based Java web app) |
| Server | Apache Tomcat 9.0.113 |
| Java | OpenJDK 25.0.3 (Temurin) |
| Load Tool | HP LoadRunner |
| Monitoring | Dynatrace OneAgent (Full-Stack mode) |
| Environment | Localhost — http://localhost:8080/jpetstore/ |
| Virtual Users | 50 Vusers |
| Test Runs | 2 (Baseline: 18 May 2026 | Post-Fix: 11 June 2026) |

---

## Objective

Simulate realistic concurrent user load on JPetStore 6 to:
- Identify performance bottlenecks under 50 concurrent users
- Monitor server-side metrics using Dynatrace APM
- Diagnose root causes of failures
- Apply fixes and validate improvement through a second test run

---

## Workload Model

| Script | Vusers | % of Load |
|---|---|---|
| Browse Categories | 25 | 50% |
| Search Product | 13 | 26% |
| Users Login | 7 | 14% |
| Place Order / Checkout | 5 | 10% |
| **Total** | **50** | **100%** |

---

## Test Run 1 — Baseline (18 May 2026)

### What Happened

Within the first few iterations, the Place Order script began failing with **Step Download Timeout (120s)** errors on the Add to Cart transaction. All 5 Place Order Vusers failed between iterations 2–4.

### Key Metrics

| Metric | Value |
|---|---|
| Avg Hits per Second | 1.553 |
| Peak Hits per Second | 2.141 |
| Avg Throughput | 7,194 bytes/sec |
| AddToCart Failures | **55 (FAIL)** |
| Thread Lock % (Dynatrace) | **97% — Critical** |
| CPU Usage (Peak) | 65.7% |
| JVM Heap Used | 57 MB |
| Avg Service Response Time | 22.67 ms |

### Errors Observed

| Error | Transaction | Description |
|---|---|---|
| LR-26999 | Add to Cart | Step Download Timeout (120s) |
| Java Exception | Cart Page | ConcurrentModificationException |
| Java Exception | Register / Account | Session Already Invalidated |

---

## Root Cause Analysis

| # | Root Cause | Impact | Evidence |
|---|---|---|---|
| 1 | Server running 2+ days without restart | Accumulated heap, stale sessions, thread exhaustion | 97% thread lock in Dynatrace |
| 2 | DB connection pool exhausted under concurrent users | Threads wait indefinitely for connections | 97% thread lock, Step Download Timeout |
| 3 | JVM heap accumulation over time | GC pauses increase, response time degrades | Dynatrace heap graph |

### Dynatrace Finding — Thread Lock Hotspot

Dynatrace identified that **96.4% of thread locking time** was caused by a single method:

```
SimpleLogger.write — Java | org.slf4j.simple
```

This confirmed the thread contention was not a database or business logic issue, but a **logging bottleneck** compounded by session state accumulation and prolonged server uptime.

---

## Fixes Applied

| # | Area | Fix |
|---|---|---|
| 1 | Script Design | Added Return to Main Menu at the end of each iteration |
| 2 | Server | Restarted Tomcat fresh before test run |
| 3 | Server Config | Increased DB connection pool size |
| 4 | Server Config | Increased Tomcat maxThreads |
| 5 | Server Config | Increased JVM heap: `-Xms512m -Xmx1024m` |

---

## Test Run 2 — Post-Fix Validation (11 June 2026)

### Result: All Issues Resolved ✅

| Metric | Before Fix | After Fix | Change |
|---|---|---|---|
| Avg Hits per Second | 1.553 | 1.924 | ↑ +23.9% |
| Avg Throughput (bytes/s) | 7,194 | 2,830 | ↓ −60.7% (lighter sessions) |
| AddToCart Failures | 55 | **0** | ✅ Fixed |
| Thread Lock % | **97%** | **< 1%** | ✅ Fully Resolved |
| CPU Usage (Peak) | 65.7% | ~20% | ↓ −70% |
| JVM Heap Used | 57 MB | ~15 MB | ↓ −74% |
| Step Download Timeout Errors | Repeated throughout run | **Zero** | ✅ Eliminated |

> **Note on Throughput:** The drop from 7,194 to 2,830 bytes/sec is expected and positive. Test 1 sessions carried bloated cart/session payloads due to session reuse. Test 2 sessions are fresh per iteration — less data transferred per request, more hits served efficiently.

---

## Folder Structure

```
JPetStore/
├── README.md
│
├── Analysis/                                   # LoadRunner Analysis exports
│   ├── LoadTest1_50Vusers_18May/               # Baseline run analysis (18 May 2026)
│   └── LoadTest2_50Vusers_11June/              # Post-fix run analysis (11 June 2026)
│
├── JPetStore Localhost Scripts/                # LoadRunner VUser scripts
│   ├── JPetStore_Browsecategories/             # Browse Categories script (25 Vusers)
│   ├── JPetStore_Login/                        # Login script (7 Vusers)
│   ├── JPetStore_PlaceOrder/                   # Place Order script (5 Vusers)
│   ├── JPetStore_RegisterUsers/                # User registration script
│   └── JPetStore_SearchProduct/                # Search Product script (13 Vusers)
│
├── Results/                                    # LoadRunner raw test results
│   ├── JpetStore_Baseline_11052026/
│   ├── JpetStore_Baseline_14052026/
│   ├── Jpetstore_Browse_Dryrun_11052026/
│   ├── JpetStore_LoadTest_50Vusers_18052026/   # Baseline load test (18 May)
│   └── JpetStore_LoadTest_50Vusers_110620260/  # Post-fix load test (11 June)
│
├── Scenario/                                   # LoadRunner Controller scenario files
│
└── Report/                                     # Consolidated test report
    └── JPetStore_LoadTest_Report_Final.docx
```

---

## Key Learnings

- **APM correlation is critical** — LoadRunner alone showed timeouts; Dynatrace pinpointed the exact method causing 96.4% thread lock
- **Throughput decrease can be a good sign** — lower bytes/sec with higher hits/sec means cleaner, more efficient sessions
- **Server state matters** — running a load test against a server that has been up for 2+ days introduces noise that masks real application behaviour

---

## Report

The full consolidated performance test report (including LoadRunner graphs, Dynatrace screenshots, transaction summary tables, root cause analysis, and before/after comparison) is available in the `/Report` folder as `JPetStore_LoadTest_Report_Final.docx`.

---

## Author

SUGANYA DEVI C
Performance Testing | HP LoadRunner | Dynatrace | ALM Quality Center
www.linkedin.com/in/suganya-devi-20161223 | ecesuganyadevi@gmail.com
