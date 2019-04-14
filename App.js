/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 *
 * @format
 * @flow
 */

import React, { useState } from 'react';
import { Button, TextInput, StyleSheet, Text, View } from 'react-native';

export default () => {
    const [number, setNumber] = useState();
    const [result, setResult] = useState();

    const performCalculation = () => {
      setResult(global.nativeTest.runTest(parseInt(number)));
    }
    
    return (
      <View style={styles.container}>
        <Text>Enter input value:</Text>
        <TextInput placeholder={"Number"} onChangeText={(t) => setNumber(t)}/>
        <Text>Result:</Text>
        <Text>{result}</Text>
        <Button onPress={performCalculation} title="Caluclate" />
      </View>
    );  
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#F5FCFF',
  },
  welcome: {
    fontSize: 20,
    textAlign: 'center',
    margin: 10,
  },
  instructions: {
    textAlign: 'center',
    color: '#333333',
    marginBottom: 5,
  },
});
