
# Nimble Protocol

## Commands

 | value | name                                        |
 | ----: | :------------------------------------------ |
 |     0 | [NOP](#nop)                                 |
 |     5 | [Game Step Request](#game-step-request)     |


### Game Step Request

| type                                                        | octets | name                                                  |
| :---------------------------------------------------------- | -----: | :---------------------------------------------------- |
| [ParticipantConnectionIndex](#participant-connection-index) |      1 | which participant connection is sending this request  |
| [UnreliableSteps]()                                         |      x | unreliable steps to add                               |


### Game Step Response

| type              | octets | name                      |
| :---------------- | -----: | :------------------------ |
| [StepId](#stepid) |      4 | last received from client |
| [ReliableSteps]() |      x | initial Game State        |

## Types

### Participant Connection Index

`uint8`.
